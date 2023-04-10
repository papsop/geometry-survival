#include "ResourceManager.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "../Debug/Logger.h"

namespace Engine
{
	void ResourceManager::VirtualOnInit()
	{
		LoadResources();
	}

	void ResourceManager::LoadResources()
	{
		DD_ASSERT(std::filesystem::exists(m_assetListFilePath), "Unable to load Assetlist");

		YAML::Node assetlist = YAML::LoadFile(m_assetListFilePath);
		for (const auto& texture : assetlist["textures"])
		{
			std::string key = texture.first.as<std::string>();
			std::string value = texture.second.as<std::string>();
		}

	}



}