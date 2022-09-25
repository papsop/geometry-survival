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

		// configurable derived classes push_back their data onto the data vector
		virtual void GetConfigurableData(ConfigurableData& data) = 0;
	};
}