#pragma once

namespace Engine
{
	template<class T>
	class SerializableField
	{
	public:
		SerializableField(std::string key, T& value) 
			: m_key(key)
			, m_value(value) {};

		~SerializableField() = default;

		void Serialize()
		{

		}

		T Deserialize();

	private:
		T& m_value;
		const std::string m_key;
	};
};