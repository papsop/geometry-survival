#include "ConfigManager.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include "../Application.h"

namespace Engine
{

	Engine::ConfigManager& ConfigManager::Get()
	{
		return Application::Instance().GetConfigManager();
	}

	void ConfigManager::VirtualOnInit()
	{
	}

	I_Cvar* ConfigManager::GetCvar(std::string name)
	{
		return m_cvars[name].get();
	}

};
