#pragma once
#include "IManager.h"
#include "../Core/Config.h"

namespace Engine
{
	class SerializationManager : public IManager
	{
	public:
		~SerializationManager() = default;
	private:
		// TODO dependency injection? xml/json etc.
		SerializationManager() = default;

		bool LoadConfig(Config& configRef);
		bool SaveConfig(const Config& configRef);
		const char* m_configFilePath = "assets/config.yaml";

	friend class Application;
	};
};