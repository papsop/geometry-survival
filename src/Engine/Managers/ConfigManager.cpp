#include "ConfigManager.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "../Application.h"
#
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
		if (m_cvars.find(name) == m_cvars.end())
		{
			LOG_WARN("Trying to retrieve unknown cvar '%s'", name.c_str());
			return nullptr;
		}
		
		return m_cvars[name].get();
	}

	void ConfigManager::LoadCvarsFromFile()
	{
		if (!std::filesystem::exists(m_configFilePath))
			return;

		YAML::Node config = YAML::LoadFile(m_configFilePath);
		for (const auto& entry : config)
		{
			std::string key = entry.first.as<std::string>();
			std::string value = entry.second.as<std::string>();
			m_cvarsFromFile.insert({ key, value });
		}

	}

	void ConfigManager::StoreModifiedCvars()
	{

		LOG_INFO("Storing cvar data to '%s'", m_configFilePath);
		std::ofstream outfile(m_configFilePath);
		YAML::Emitter out;
		out << YAML::BeginMap;

		for (auto&& cvarEntry : m_cvars)
		{
			auto cvar = cvarEntry.second.get();
			if (cvar->GetIsModified())
			{
				out << YAML::Key << cvar->GetKey();
				out << YAML::Value << cvar->GetValueAsString();
			}
		}
		out << YAML::EndMap;

		outfile << out.c_str();
		outfile.close();
	}

};
