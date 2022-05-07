#pragma once

namespace Engine
{
	template<class T>
	class SerializableField
	{
	public:
		using type = T;
		SerializableField(T value) 
			: m_value(value) {};

		~SerializableField() = default;

		void Serialize()
		{

		}

		T Deserialize();

	private:
		T m_value;
	};
};