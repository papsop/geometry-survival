#include "ConfigManager.h"

namespace Engine
{

	template<typename T>
	void ConfigManager::RegisterConfigValue(std::string key, T defaultValue)
	{
		const char* typeIdOfT = typeid(T).name();
		ConfigEntry entry;
		entry.Value = defaultValue;
		entry.TypeName = typeIdOfT;
		m_configData[key] = entry;
	}

	template<typename T>
	void ConfigManager::SetValue(std::string key, T value)
	{
		const char* typeIdOfT = typeid(T).name();
		DD_ASSERT(m_configData.find(key) != m_configData.end(), "Trying to set a nonexistent config key '%s'", key);
		DD_ASSERT(typeIdOfT != m_configData[key].TypeName, "Trying to change type of '%s' config entry (not allowed)", key);
		ConfigEntry entry;
		entry.Value = value;
		entry.TypeName = typeIdOfT;
		m_configData[key] = entry;
	}

	template<typename T>
	T ConfigManager::GetValue(std::string key)
	{
		DD_ASSERT(m_configData.find(key) != m_configData.end(), "Trying to retrieve a nonexistent config key '%s'", key);
		return std::any_cast<T>(m_configData[key].Value);
	}
};