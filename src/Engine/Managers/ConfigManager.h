#pragma once
#include "IManager.h"
#include "../Debug/Logger.h"
#include <unordered_map>
#include <any>

namespace Engine
{

	struct ConfigEntry
	{
		const char* Key;
		const char* TypeName;
		std::any Value;
	};

	class ConfigManager : public IManager
	{
	public:
		static ConfigManager& Get();
		~ConfigManager() = default;
		
		template<typename T>
		void RegisterConfigValue(std::string key, T defaultValue);
		template<>
		void RegisterConfigValue(std::string key, const char* defaultValue);

		template<typename T>
		void SetValue(std::string key, T value);
		template<>
		void SetValue(std::string key, const char* value);

		template<typename T>
		T GetValue(std::string key);

		bool StoreValuesToFile();
		void LoadValuesFromFile();
	private:
		ConfigManager() = default;
		void VirtualOnInit() override;

		const char* m_configFilePath = "assets/config.yaml";
		std::unordered_map<std::string, ConfigEntry> m_configData;

	friend class Application;
	};
};

#include "ConfigManager.inl"