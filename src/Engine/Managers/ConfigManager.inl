#include "ConfigManager.h"

namespace Engine
{
	template<typename T>
	void ConfigManager::SetValue(std::string key, T value)
	{
		m_configData[key] = value;
	}

	template<typename T>
	T ConfigManager::GetValue(std::string key)
	{
		if (m_configData.find(key) != m_configData.end())
		{
			return std::any_cast<T>(m_configData[key]);
		}
		return {};
	}
};