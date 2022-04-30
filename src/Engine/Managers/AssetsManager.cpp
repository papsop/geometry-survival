#include "AssetsManager.h"
#include "../Application.h"
#include <yaml-cpp/yaml.h>

namespace Engine
{

	AssetsManager& AssetsManager::Get()
	{
		return Application::Instance().GetAssetsManager();
	}

	Engine::Config AssetsManager::LoadEngineConfig()
	{
		YAML::Node configNode = YAML::LoadFile(m_configFileName);
		Config config;
		config.WindowHeight = configNode["WindowHeight"].as<unsigned int>();
		config.WindowWidth = configNode["WindowWidth"].as<unsigned int>();
		config.WindowName = configNode["WindowName"].as<std::string>();
		return config;
	}

}