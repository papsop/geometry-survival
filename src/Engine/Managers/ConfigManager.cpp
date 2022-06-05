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
		SetValue("window_width", 1024);
		SetValue("window_height", 768);
		SetValue("window_name", "Dungeons & Geometry");
		SetValue("window_fullscreen", false);
	}

	bool ConfigManager::StoreValuesToFile()
	{
		return true;
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

};
