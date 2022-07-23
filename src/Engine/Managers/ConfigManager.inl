#include "ConfigManager.h"
#include "../Debug/Logger.h"

namespace Engine
{
	template<typename T>
	void ConfigManager::RegisterCvar(std::string name, T* ptr, T defaultValue, std::function<void(void)> func)
	{
		DD_ASSERT(m_cvars.find(name) == m_cvars.end(), "'%s' cvar already registered", name.c_str());

		*ptr = defaultValue;
		auto cvar = std::unique_ptr<I_Cvar>( new CvarWrapper<T>(name, ptr, defaultValue, func) );
		
		if (m_cvarsFromFile.find(name) != m_cvarsFromFile.end())
			cvar->SetValueString(m_cvarsFromFile[name]);

		m_cvars.insert({ name, std::move(cvar) });
	}
};