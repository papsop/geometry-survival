#pragma once
#include "IManager.h"
#include <unordered_map>
#include <any>

namespace Engine
{
	class ConfigManager : public IManager
	{
	public:
		static ConfigManager& Get();
		~ConfigManager() = default;
		
		template<typename T>
		void SetValue(std::string key, T value);

		template<typename T>
		T GetValue(std::string key);

		bool StoreValuesToFile();
	private:
		ConfigManager() = default;
		void VirtualOnInit() override;

		const char* m_configFilePath = "assets/config.yaml";
		std::unordered_map<std::string, std::any> m_configData;

	friend class Application;
	};
};

#include "ConfigManager.inl"