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

	void ConfigManager::RegisterConfigurable(IConfigurable* configurable)
	{
		m_configurables.emplace_back(configurable);
	}

	void ConfigManager::UnregisterConfigurable(IConfigurable* configurable)
	{
		m_configurables.erase(std::remove(m_configurables.begin(), m_configurables.end(), configurable), m_configurables.end());
	}

	void ConfigManager::RegisterCvar(std::string name, int* ptr, int defaultValue)
	{
		if (m_cvarsFromFile.find(name) != m_cvarsFromFile.end())
			*ptr = std::stoi(m_cvarsFromFile[name]);
		else
			*ptr = defaultValue;
	}

	void ConfigManager::RegisterCvar(std::string name, float* ptr, float defaultValue)
	{
		if (m_cvarsFromFile.find(name) != m_cvarsFromFile.end())
			*ptr = std::stof(m_cvarsFromFile[name]);
		else
			*ptr = defaultValue;
	}

	void ConfigManager::RegisterCvar(std::string name, std::string* ptr, std::string defaultValue)
	{
		if (m_cvarsFromFile.find(name) != m_cvarsFromFile.end())
			*ptr = m_cvarsFromFile[name];
		else
			*ptr = defaultValue;
	}

	void ConfigManager::StoreModifiedCvars()
	{
    IConfigurable::ConfigurableData configurableData = {};
    for (auto&& configurable : m_configurables)
    {
      configurable->GetConfigurableData(configurableData);
    }

		LOG_INFO("Storing cvar data to '%s'", m_configFilePath);
		std::ofstream outfile(m_configFilePath);
		YAML::Emitter out;
		out << YAML::BeginMap;

    for (auto&& entry : configurableData)
    {
      out << YAML::Key << entry.first;
      out << YAML::Value << entry.second;
    }

		out << YAML::EndMap;

		outfile << out.c_str();
		outfile.close();
	}

	// ==========================================================================
	// IConfigurable
	// ==========================================================================

	IConfigurable::IConfigurable()
	{
		ConfigManager::Get().RegisterConfigurable(this);
	}

	IConfigurable::~IConfigurable()
	{
		ConfigManager::Get().UnregisterConfigurable(this);
	}

};
