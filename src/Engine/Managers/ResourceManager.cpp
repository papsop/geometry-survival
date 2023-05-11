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
		
		// Dummy image
		sf::Image pinkImage;
		pinkImage.create(16, 16, {255, 0, 127, 255});
		m_dummyTexture = std::make_shared<sf::Texture>();
		m_dummyTexture->loadFromImage(pinkImage);

		// Dummy shader
    const std::string fragmentShader = \
      "void main()" \
      "{" \
      "    gl_FragColor = vec4(gl_TexCoord[0].x, gl_TexCoord[0].y, gl_TexCoord[0].x, 1.0);" \
      "}";
		m_dummyShader = std::make_shared<sf::Shader>();
		m_dummyShader->loadFromMemory(fragmentShader, sf::Shader::Fragment);

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
		// TODO: split into 2 functions?
		// TexturesIndex
		try 
		{
			DD_ASSERT(std::filesystem::exists(m_texturesIndexPath), "Unable to find TexturesIndex, searching path '%s'", m_texturesIndexPath);
			YAML::Node texturesList = YAML::LoadFile(m_texturesIndexPath);

			for (auto& texture : texturesList)
			{
				auto name = texture.first.as<std::string>();
				auto path = m_assetsFolder + texture.second["path"].as<std::string>();

				m_textures[name] = LoadTextureFromFile(path);
			}
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("Exception while parsing TexturesIndex: %s", e.what());
		}

		// Shaders Index
		try
		{
			DD_ASSERT(std::filesystem::exists(m_shadersIndexPath), "Unable to find ShadersIndex, searching path '%s'", m_shadersIndexPath);
			YAML::Node shadersList = YAML::LoadFile(m_shadersIndexPath);

			for (auto& shader : shadersList)
			{
				auto name = shader.first.as<std::string>();
				std::string fragmentPath;
				std::string vertexPath;
				if (shader.second["fragment_path"])
				{
					fragmentPath = m_assetsFolder + shader.second["fragment_path"].as<std::string>();
				}
        if (shader.second["vertex_path"])
        {
          vertexPath = m_assetsFolder + shader.second["vertex_path"].as<std::string>();
        }

				m_shaders[name] = LoadShaderFromFiles(fragmentPath, vertexPath);
			}
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("Exception while parsing ShaderIndex: %s", e.what());
		}
	}

  std::shared_ptr<sf::Texture> ResourceManager::LoadTextureFromFile(std::string filePath)
  {
		if (!std::filesystem::exists(filePath))
		{
			LOG_ERROR("Unable to find texture at '%s'", filePath);
			return m_dummyTexture;
		}

		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
		texture->loadFromFile(filePath);
		return texture;
  }

  std::shared_ptr<sf::Shader> ResourceManager::LoadShaderFromFiles(std::string fragmentPath, std::string vertexPath)
  {
    if (!fragmentPath.empty() && !std::filesystem::exists(fragmentPath))
    {
      LOG_ERROR("Unable to find fragment shader at '%s'", fragmentPath);
			return m_dummyShader;
    }
    if (!vertexPath.empty() && !std::filesystem::exists(vertexPath))
    {
      LOG_ERROR("Unable to find vertex shader at '%s'", vertexPath);
      return m_dummyShader;
    }

    std::shared_ptr<sf::Shader> shader = std::make_shared<sf::Shader>();
    
		if(!fragmentPath.empty())
			shader->loadFromFile(fragmentPath, sf::Shader::Fragment);
    if (!vertexPath.empty())
      shader->loadFromFile(vertexPath, sf::Shader::Vertex);

    return shader;
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

		std::shared_ptr<sf::Texture> texture;
		if (m_textures.find(fullResourceName) != m_textures.end())
		{
			texture = m_textures[fullResourceName];
		}
		else
		{
			texture = std::make_shared<sf::Texture>();
		}

		texture->loadFromFile(filePath);
		m_textures[fullResourceName] = texture;
	}

	void ResourceManager::LoadShaderResourceYAML(std::string topLevel, YAML::Node& node)
	{
		auto name = node["name"].as<std::string>();

		auto fullResourceName = topLevel + "/" + name;
		
		std::shared_ptr<sf::Shader> shader;
		if (m_shaders.find(fullResourceName) != m_shaders.end())
		{
			shader = m_shaders[fullResourceName];
		}
		else
		{
			shader = std::make_shared<sf::Shader>();
		}

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

	// Usage: LoadTextureResource("player")
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
			if (ImGui::Button("Reload resources"))
			{
				LoadResourcesList();
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