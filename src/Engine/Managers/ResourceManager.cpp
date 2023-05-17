#include "ResourceManager.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <stdexcept>

#include <iostream>
#include "../imgui/imgui.h"
#include "../Debug/Logger.h"
#include "../Application.h"
#include "../Utils/VectorUtils.h"
#include "../Core/CustomYAMLTypes.h"

namespace Engine
{
	void ResourceManager::VirtualOnInit()
	{
		IDebuggable::DebuggableOnInit();
		GenerateDummyResources();
		LoadResourcesList();
	}

	void ResourceManager::VirtualOnDestroy()
	{
		IDebuggable::DebuggableOnDestroy();
	}


	Engine::ResourceManager& ResourceManager::Get()
	{
		return Application::Instance().GetResourceManager();
	}

  void ResourceManager::GenerateDummyResources()
  {
    // Dummy image
    sf::Image pinkImage;
    pinkImage.create(16, 16, { 255, 0, 127, 255 });
    m_dummyTexture = std::make_shared<sf::Texture>();
    m_dummyTexture->loadFromImage(pinkImage);
  }

	// ============================
	// Resource loading
	// ============================
	void ResourceManager::LoadResourcesList()
	{
		// TODO: SPLIIIIIIIIIIIIIIIIIIIIIIIT
		// TexturesIndex
		try 
		{
			DD_ASSERT(std::filesystem::exists(m_texturesIndexPath), "Unable to find TexturesIndex, searching path '%s'", m_texturesIndexPath);
			YAML::Node texturesList = YAML::LoadFile(m_texturesIndexPath);

			for (auto& texture : texturesList)
			{
				auto name = texture.first.as<std::string>();
				auto path = m_assetsFolder + texture.second["path"].as<std::string>();

				// shit code, YAML::Node -> bool doesnt exists
				// but you can use it in if(YAML::Node)
				bool isRepeatable = false;
				if(texture.second["repeatable"] && texture.second["repeatable"].as<bool>())
					isRepeatable = true;
					
				if (m_textures.find(name) == m_textures.end())
				{
					m_textures[name] = std::make_shared<sf::Texture>();
				}

				LoadTextureFromFile(m_textures[name].get(), path, isRepeatable);
				if (!m_textures[name])
				{
					LOG_ERROR("Unable to load texture '%s' at '%s", name, path);
					continue; // gg go next
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("Exception while parsing TexturesIndex: %s", e.what());
		}

		// ShadersIndex
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

				if (m_shaders.find(name) == m_shaders.end())
				{
					m_shaders[name] = std::make_shared<sf::Shader>();
				}
				LoadShaderFromFiles(m_shaders[name].get(), fragmentPath, vertexPath);
				if (!m_shaders[name])
				{
					LOG_ERROR("Unable to load shader '%s' at [frag: '%s', vertex: '%s']", name, fragmentPath, vertexPath);
					continue; // gg go next
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("Exception while parsing ShaderIndex: %s", e.what());
		}

		// AnimationsIndex
		try
		{
			DD_ASSERT(std::filesystem::exists(m_animationsIndexPath), "Unable to find AnimationsIndex, searching path '%s'", m_animationsIndexPath);
			YAML::Node animationsList = YAML::LoadFile(m_animationsIndexPath);

			for (auto& animation : animationsList)
			{
				auto name = animation.first.as<std::string>();
				auto textureName = animation.second["texture"].as<std::string>();
				//auto texture = GetTexture(textureName.c_str());

				if (m_animations.find(name) == m_animations.end())
				{
					m_animations[name] = std::make_shared<AnimationClip>();
				}

				auto& clip = m_animations[name];
				clip->Name = name;
				clip->TextureName = textureName;
				clip->SampleTextureSize = animation.second["frame_size"].as<sf::Vector2i>();
				clip->Loopable = animation.second["loopable"].as<bool>();
				clip->Samples = {};
				std::string samplesType = animation.second["samples_type"].as<std::string>();
				if (samplesType == "per_sample")
				{
					for (auto& sample : animation.second["samples"])
					{
						AnimationSample s;
						s.Duration = sample["duration"].as<float>();
						s.TextureCoord = sample["coords"].as<sf::Vector2i>();
						clip->Samples.emplace_back(s);
					}
				}
				else if (samplesType == "fps")
				{
					int samplesCount = animation.second["samples_count"].as<int>();
					float sampleDuration = 1.0f / animation.second["fps"].as<int>();
					for (int i = 0; i < samplesCount; i++)
					{
						AnimationSample s;
						s.Duration = sampleDuration;
						s.TextureCoord.x = clip->SampleTextureSize.x * i;
						s.TextureCoord.y = 0;
						clip->Samples.emplace_back(s);
					}
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("Exception while parsing AnimationsList: %s", e.what());
		}
	}

  void ResourceManager::LoadTextureFromFile(sf::Texture* target, std::string filePath, bool isRepeatable)
  {
		if (!std::filesystem::exists(filePath))
		{
			LOG_ERROR("Unable to find texture at '%s', using dummyTexture", filePath);
			target = nullptr;
			return;
		}

		target->loadFromFile(filePath);
		target->setRepeated(isRepeatable);
  }

  void ResourceManager::LoadShaderFromFiles(sf::Shader* target, std::string fragmentPath, std::string vertexPath)
  {
    if (!fragmentPath.empty() && !std::filesystem::exists(fragmentPath))
    {
      LOG_ERROR("Unable to find fragment shader at '%s', can't load shader", fragmentPath);
			target = nullptr;
			return;
    }
    if (!vertexPath.empty() && !std::filesystem::exists(vertexPath))
    {
      LOG_ERROR("Unable to find vertex shader at '%s', can't load shader", vertexPath);
			target = nullptr;
      return;
    }

		if(!fragmentPath.empty())
			target->loadFromFile(fragmentPath, sf::Shader::Fragment);
    if (!vertexPath.empty())
			target->loadFromFile(vertexPath, sf::Shader::Vertex);
  }

	void ResourceManager::LoadAnimationData(AnimationClip* target, YAML::Node)
	{
		/* todo split */
	}

	// Usage: GetTexture("player")
	std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const char* name)
	{
    if (m_textures.find(name) == m_textures.end())
    {
      LOG_ERROR("Unable to GetTexture with name '%s', using dummyTexture", name);
      return m_dummyTexture;
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

	std::shared_ptr<Engine::AnimationClip> ResourceManager::GetAnimation(const char* name)
	{
		if (m_animations.find(name) == m_animations.end())
		{
			LOG_ERROR("Unable to GetAnimation with name '%s'", name);
			return nullptr;
		}
		return m_animations[name];
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

}