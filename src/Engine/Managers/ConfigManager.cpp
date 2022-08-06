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

	void ConfigManager::UnregisterCvar(std::string name)
	{
		if (m_cvars.find(name) != m_cvars.end())
			return;
			
		if(m_cvars[name]->IsDirty())
			m_unregisteredCvars[name] = m_cvars[name]->GetValueAsString();

		m_cvars.erase(name);
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

		// store still registered cvars
		for (auto&& cvarEntry : m_cvars)
		{
			auto cvar = cvarEntry.second.get();
			if (cvar->IsDirty())
			{
				out << YAML::Key << cvar->GetKey();
				out << YAML::Value << cvar->GetValueAsString();
			}
		}

		// store dirty cvars that unregistered before storing
		for (auto&& cvarEntry : m_unregisteredCvars)
		{
			out << YAML::Key << cvarEntry.first;
			out << YAML::Value << cvarEntry.second;
		}

		out << YAML::EndMap;

		outfile << out.c_str();
		outfile.close();
	}

};
