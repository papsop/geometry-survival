#include "ResourceManager.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <stdexcept>
#include <iostream>
#include "../Debug/Logger.h"
#include "../Application.h"

namespace Engine
{


	void ResourceManager::VirtualOnInit()
	{
		LoadResourcesList();
	}

	void ResourceManager::VirtualOnDestroy()
	{
// 		for (auto& container : m_resourceContainers)
// 		{
// 			delete container.second;
// 		}
	}


	Engine::ResourceManager& ResourceManager::Get()
	{
		return Application::Instance().GetResourceManager();
	}

	// Usage: LoadResource("textures/player")
	std::shared_ptr<sf::Texture> ResourceManager::LoadTextureResource(const char* name)
	{
		if (m_resources.find(name) == m_resources.end())
		{
			// TODO: pink texture
			return nullptr;
		}

		std::string filePath = m_assetsFolder + m_resources[name];

		if (!std::filesystem::exists(m_assetListFilePath))
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

					m_resources[topLevel + "/" + name] = path;
				}
			}
		}
		catch (std::exception e)
		{
			LOG_ERROR("Exception while parsing AssetList: %s", e.what());
		}
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