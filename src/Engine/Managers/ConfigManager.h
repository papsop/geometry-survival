#pragma once
#include "IManager.h"
#include "../Debug/Logger.h"
#include <unordered_map>
#include <any>
#include "Config/IConfigurable.h"

namespace Engine
{
	// config manager
	class ConfigManager : public IManager
	{
	public:

		static ConfigManager& Get();
		~ConfigManager() = default;

		void RegisterCvar(std::string name, int* ptr, int defaultValue);
		void RegisterCvar(std::string name, float* ptr, float defaultValue);
		void RegisterCvar(std::string name, std::string* ptr, std::string defaultValue);

		void StoreModifiedCvars();
		void LoadCvarsFromFile();

		void RegisterConfigurable(IConfigurable*);
		void UnregisterConfigurable(IConfigurable*);
	private:
		ConfigManager() = default;
		void VirtualOnInit() override;

		const char* m_configFilePath = "assets/config.yaml";
		
		std::unordered_map<std::string, std::string> m_cvarsFromFile;
		std::vector<IConfigurable*> m_configurables;

	friend class Application;
	};

};