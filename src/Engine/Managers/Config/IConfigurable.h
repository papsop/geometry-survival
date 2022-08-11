#pragma once

namespace Engine
{
	class IConfigurable
	{
	public:
		using ConfigurableEntry = std::pair<std::string, std::string>;
		using ConfigurableData = std::vector<ConfigurableEntry>;

		IConfigurable();
		virtual ~IConfigurable();

		// configurable derived classes should return vector of key-values to store into config
		virtual ConfigurableData GetConfigurableData() = 0;
	};
}