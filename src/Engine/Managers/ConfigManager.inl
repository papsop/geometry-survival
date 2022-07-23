#include "ConfigManager.h"

namespace Engine
{
	template<typename T>
	void ConfigManager::RegisterCvar(std::string name, T* ptr, T defaultValue, std::function<void(void)> func)
	{
		*ptr = defaultValue;
		auto cvar = std::unique_ptr<I_Cvar>( new CvarWrapper<T>(name, ptr, defaultValue, func) );
		m_cvars.insert({ name, std::move(cvar) });
	}
};