#pragma once
#include "IManager.h"
#include "../Debug/Logger.h"
#include "../Utils/CvarUtils.h"
#include <unordered_map>
#include <any>

namespace Engine
{
	// config manager
	class ConfigManager : public IManager
	{
	public:

		static ConfigManager& Get();
		~ConfigManager() = default;

		template<typename T>
		void RegisterCvar(std::string name, T* ptr, T defaultValue, std::function<void(void)> func = nullptr);

		I_Cvar* GetCvar(std::string name);

		void StoreModifiedCvars();
		void LoadCvarsFromFile();

	private:
		ConfigManager() = default;
		void VirtualOnInit() override;

		const char* m_configFilePath = "assets/config.yaml";
		std::unordered_map<std::string, std::unique_ptr<I_Cvar>> m_cvars;
		std::unordered_map<std::string, std::string> m_cvarsFromFile;

	friend class Application;
	};

};

#include "ConfigManager.inl"