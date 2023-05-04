#include "ResourceManager.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <stdexcept>
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
	std::shared_ptr<sf::Texture> ResourceManager::LoadTextureResource(std::string name)
	{
		std::string topLevel = name.substr(0, name.find('/'));
		DD_ASSERT(m_resources.find(topLevel) != m_resources.end(), "Unable to find toplevel '%s' in the assetlist", topLevel.c_str());

		std::string assetName = name.substr(name.find('/') + 1);
		DD_ASSERT(m_resources[topLevel].find(assetName) != m_resources[topLevel].end(), "Unable to find asset named '%s' in toplevel '%s'", assetName.c_str(), topLevel.c_str());

		std::string path = "assets/" + m_resources[topLevel][assetName];
		DD_ASSERT(std::filesystem::exists(m_assetListFilePath), "Can't find file '%s'", path.c_str())

		if (m_textures.find(path) == m_textures.end())
		{
			std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(path);
			m_textures[path] = texture;
		}

		return m_textures[path];
	}

	void ResourceManager::LoadResourcesList()
	{
		DD_ASSERT(std::filesystem::exists(m_assetListFilePath), "Unable to find Assetlist, searching path '%s'", m_assetListFilePath);

		try 
		{
			YAML::Node assetList = YAML::LoadFile(m_assetListFilePath);
			// store top level nodes into map
			for (auto& node : assetList)
			{
				std::string topLevel = node.first.as<std::string>();

				if (m_resources.find(topLevel) == m_resources.end())
					m_resources[topLevel] = {};

				for (auto& subNode : node.second)
				{
					std::string name = subNode["name"].as<std::string>();
					std::string path = subNode["path"].as<std::string>();

					m_resources[topLevel][name] = path;
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