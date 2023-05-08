#include "ResourceManager.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <stdexcept>

#include <iostream>
#include "../imgui/imgui.h"
#include "../Debug/Logger.h"
#include "../Application.h"

namespace Engine
{


	void ResourceManager::VirtualOnInit()
	{
		IDebuggable::DebuggableOnInit();
		LoadResourcesList();
	}

	void ResourceManager::VirtualOnDestroy()
	{
		IDebuggable::DebuggableOnDestroy();
// 		for (auto& container : m_resourceContainers)
// 		{
// 			delete container.second;
// 		}
	}


	Engine::ResourceManager& ResourceManager::Get()
	{
		return Application::Instance().GetResourceManager();
	}

	// ============================
	// Resource loading
	// ============================
	void ResourceManager::LoadResourcesList()
	{
		DD_ASSERT(std::filesystem::exists(m_assetListFilePath), "Unable to find Assetlist, searching path '%s'", m_assetListFilePath);

		try
		{
			YAML::Node assetList = YAML::LoadFile(m_assetListFilePath);

			// TODO: Any number of subnodes, some kind of graph 
			// traversal to get all the paths to each resource
			// YAML won't let me access the graph pointers, 
			// so it might be annoying to work with
			// = For now let's only support TopLevel + resource
			for (auto& node : assetList)
			{
				std::string topLevel = node.first.as<std::string>();
				for (auto& subNode : assetList[topLevel])
				{
					if (subNode.IsMap())
					{
						auto resourceType = subNode["resource"].as<std::string>();
						if (resourceType == "texture")
							LoadTextureResourceYAML(topLevel, subNode);
						else if (resourceType == "shader")
							LoadShaderResourceYAML(topLevel, subNode);
					}
				}
			}
		}
		catch (std::exception e)
		{
			LOG_ERROR("Exception while parsing AssetList: %s", e.what());
		}
	}

	void ResourceManager::LoadTextureResourceYAML(std::string topLevel, YAML::Node& node)
	{
		auto name = node["name"].as<std::string>();
		auto path = node["path"].as<std::string>();

		auto fullResourceName = topLevel + "/" + name;
		auto filePath = m_assetsFolder + path;

		if (!std::filesystem::exists(filePath))
		{
			LOG_ERROR("Unable to find file at '%s'", filePath.c_str());
			return;
		}

		if (m_textures.find(fullResourceName) != m_textures.end())
		{
			LOG_ERROR("Texture with name '%s' already loaded", fullResourceName.c_str());
			return;
		}

		auto texture = std::make_shared<sf::Texture>();
		texture->loadFromFile(filePath);
		m_textures[fullResourceName] = texture;
	}

	void ResourceManager::LoadShaderResourceYAML(std::string topLevel, YAML::Node& node)
	{
		auto name = node["name"].as<std::string>();

		auto fullResourceName = topLevel + "/" + name;

		if (m_shaders.find(fullResourceName) != m_shaders.end())
		{
			LOG_ERROR("Shader with name '%s' already loaded", fullResourceName.c_str());
			return;
		}

		auto shader = std::make_shared<sf::Shader>();
		if (node["vertex_path"])
		{
			auto vertexPath = m_assetsFolder + node["vertex_path"].as<std::string>();
			shader->loadFromFile(vertexPath, sf::Shader::Vertex);
		}
		if (node["fragment_path"])
		{
			auto fragmentPath = m_assetsFolder + node["fragment_path"].as<std::string>();
			shader->loadFromFile(fragmentPath, sf::Shader::Fragment);
		}
		m_shaders[fullResourceName] = shader;
	}

	// Usage: LoadTextureResource("textures/player")
	std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const char* name)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			LOG_ERROR("Unable to GetTexture with name '%s'", name);
			return nullptr;
		}
		return m_textures[name];
	}

	std::shared_ptr<sf::Shader> ResourceManager::GetShader(const char* name)
	{
		if (m_shaders.find(name) == m_shaders.end())
		{
			LOG_ERROR("Unable to GetShader with name '%s'", name);
			return nullptr;
		}
		return m_shaders[name];
	}

	void ResourceManager::Debug(VisualDebugContext& debugContext)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(100.f, 100.f), ImGuiCond_Once, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize;

		if (ImGui::Begin("ResourceManager", NULL, window_flags))
		{
			ImGui::Text("Loaded resources:");
			ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
			if (ImGui::BeginTable("LoadedTextures", 2, tableFlags))
			{
				ImGui::TableSetupColumn("Name");
				ImGui::TableSetupColumn("Use_count");
				ImGui::TableHeadersRow();
				for (const auto& entry : m_textures)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%s", entry.first.c_str());
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%d", entry.second.use_count());
				}
				ImGui::EndTable();
			}

			if (ImGui::BeginTable("LoadedShaders", 2, tableFlags))
			{
				ImGui::TableSetupColumn("Name");
				ImGui::TableSetupColumn("Use_count");
				ImGui::TableHeadersRow();
				for (const auto& entry : m_shaders)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%s", entry.first.c_str());
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%d", entry.second.use_count());
				}
				ImGui::EndTable();
			}

		}
		ImGui::End();
	}

	// ============================
	template<>
	TextureResource ResourceContainer<TextureResource>::LoadResourceImpl(const char* name)
	{
		// TODO: actually load a template
		TextureResource resource;
		resource.Texture = sf::Texture();
		resource.FilePath = name;
		return resource;
	}
}