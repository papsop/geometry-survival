#pragma once
#include <utility>
#include <string>

namespace Engine
{
	class IConfigurable
	{
	public:
		using ConfigurableEntry = std::pair<std::string, std::string>;
		using ConfigurableData = std::vector<ConfigurableEntry>;

		IConfigurable();
		virtual ~IConfigurable();

		// configurable derived classes should return a vector of key-values to store into config
		virtual ConfigurableData GetConfigurableData() = 0;
	};
}