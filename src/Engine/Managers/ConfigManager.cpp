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
		RegisterConfigValue("window_width", 800);
		RegisterConfigValue("window_height", 600);
		RegisterConfigValue("window_name", "Dungeons & Geometry");
		RegisterConfigValue("window_fullscreen", false);


		LoadValuesFromFile();
	}

	bool ConfigManager::StoreValuesToFile()
	{
		YAML::Emitter out;
		out << YAML::BeginMap;

		for (const auto& entry : m_configData)
		{
			out << YAML::Key << entry.first;
			out << YAML::Value;
			
			// think of something better plz
			if( entry.second.TypeName == typeid(int).name())
				out << std::any_cast<int>(entry.second.Value);
			else if (entry.second.TypeName == typeid(bool).name())
				out << std::any_cast<bool>(entry.second.Value);
			else if (entry.second.TypeName == typeid(float).name())
				out << std::any_cast<float>(entry.second.Value);
			else if (entry.second.TypeName == typeid(const char*).name())
				out << std::any_cast<const char*>(entry.second.Value);
		}

		out << YAML::EndMap;

		std::ofstream fout(m_configFilePath);
		fout << out.c_str();
		return true;
	}

	void ConfigManager::LoadValuesFromFile()
	{
		if (!std::filesystem::exists(m_configFilePath))
			return;

		YAML::Node data = YAML::LoadFile(m_configFilePath);

		for (auto& entry : m_configData)
		{
			auto yamlData = data[entry.first];
			if (!yamlData.IsDefined())
				continue; // just skip if not present

			if (entry.second.TypeName == typeid(int).name())
				entry.second.Value = yamlData.as<int>();
			else if (entry.second.TypeName == typeid(bool).name())
				entry.second.Value = yamlData.as<bool>();
			else if (entry.second.TypeName == typeid(float).name())
				entry.second.Value = yamlData.as<float>();
			else if (entry.second.TypeName == typeid(std::string).name())
				entry.second.Value = yamlData.as<std::string>();
		}
	}

	//bool SerializationManager::LoadConfig(Config& configRef)
	//{
	//	if (!std::filesystem::exists(m_configFilePath))
	//		return false;

	//	YAML::Node data = YAML::LoadFile(m_configFilePath);
	//	
	//	auto configData = data["Config"];
	//	if (!configData.IsDefined())
	//		return false;
	//	
	//	auto engineData = configData["Engine"];
	//	if (!engineData.IsDefined())
	//		return false;

	//	auto windowData = engineData["Window"];
	//	if (!windowData.IsDefined())
	//		return false;

	//	if (windowData["Width"]) configRef.Engine.Window.Width = windowData["Width"].as<uint32_t>();
	//	if (windowData["Height"]) configRef.Engine.Window.Height = windowData["Height"].as<uint32_t>();
	//	if (windowData["Name"]) configRef.Engine.Window.Name = windowData["Name"].as<std::string>();
	//	if (windowData["Fullscreen"]) configRef.Engine.Window.Fullscreen = windowData["Fullscreen"].as<bool>();

	//	return true;
	//}

	//bool SerializationManager::SaveConfig(const Config& configRef)
	//{
	//	YAML::Emitter out;
	//	out << YAML::BeginMap;						// File start
	//	out << YAML::Key << "Config";
	//	out << YAML::Value;
	//	out << YAML::BeginMap;						// Config start
	//	out << YAML::Key << "Engine";
	//	out << YAML::BeginMap;						// Engine start

	//	// ++++++WINDOW
	//	out << YAML::Key << "Window";
	//	out << YAML::BeginMap;						// Window start

	//	out << YAML::Key << "Width" << YAML::Value << configRef.Engine.Window.Width;
	//	out << YAML::Key << "Height" << YAML::Value << configRef.Engine.Window.Height;
	//	out << YAML::Key << "Name" << YAML::Value << configRef.Engine.Window.Name;
	//	out << YAML::Key << "Fullscreen" << YAML::Value << configRef.Engine.Window.Fullscreen;
	//	out << YAML::EndMap;						// Window end
	//	// ------WINDOW

	//	out << YAML::EndMap;						// Engine end
	//	out << YAML::EndMap;						// Config end
	//	out << YAML::EndMap;						// File end
	//	std::ofstream fout(m_configFilePath);
	//	fout << out.c_str();
	//	return true;
	//}


	// string is special
	template<>
	void ConfigManager::RegisterConfigValue(std::string key, const char* defaultValue)
	{
		ConfigEntry entry;
		std::string str = defaultValue;
		entry.Value = str;
		entry.TypeName = typeid(std::string).name();
		m_configData[key] = entry;
	}

	template<>
	void ConfigManager::SetValue(std::string key, const char* value)
	{
		const char* typeIdOfString = typeid(std::string).name();
		DD_ASSERT(m_configData.find(key) != m_configData.end(), "Trying to set a nonexistent config key '%s'", key);
		DD_ASSERT(typeIdOfString != m_configData[key].TypeName, "Trying to change type of '%s' config entry (not allowed)", key);
		ConfigEntry entry;
		std::string str = value;
		entry.Value = str;
		entry.TypeName = typeIdOfString;
		m_configData[key] = entry;
	}

};
