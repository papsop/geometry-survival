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

			// TODO: We should be able to support multiple types
			//   - texture:
			//			name: bullet
			//			path : sprites / bullet.png
			// maybe use the "- texture" as a resourceType classifier
			for (auto& node : assetList)
			{
				std::string topLevel = node.first.as<std::string>();
				for (auto& subNode : assetList[topLevel])
				{
					std::string name = subNode["name"].as<std::string>();
					std::string path = subNode["path"].as<std::string>();

					m_resourceNamesToPaths[topLevel + "/" + name] = path;
				}
			}
		}
		catch (std::exception e)
		{
			LOG_ERROR("Exception while parsing AssetList: %s", e.what());
		}
	}

	// Usage: LoadTextureResource("textures/player")
	std::shared_ptr<sf::Texture> ResourceManager::LoadTextureResource(const char* name)
	{
		if (m_resourceNamesToPaths.find(name) == m_resourceNamesToPaths.end())
		{
			// TODO: pink texture
			return nullptr;
		}

		std::string filePath = m_assetsFolder + m_resourceNamesToPaths[name];

		if (!std::filesystem::exists(filePath))
		{
			// TODO: pink texture
			return nullptr;
		}

		if (m_textures.find(filePath) == m_textures.end())
		{
			std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(filePath);
			m_textures[filePath] = texture;
		}

		return m_textures[filePath];
	}

	std::shared_ptr<sf::Shader> ResourceManager::LoadShaderResource(const char* name)
	{
		return nullptr;
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