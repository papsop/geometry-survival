#pragma once

namespace Engine
{
	template<typename... Args>
	auto Fields(Args&&... args);

	template<typename Class>
	inline auto RegisterFields()
	{
		return std::make_tuple();
	}

	template<typename Class, typename T>
	class SerializableField
	{
	public:
		using member_ptr_t = T Class::*;					// T Pointer to a member of Class
		using class_type = Class;
		using member_type = T;
		
		SerializableField(const char* name, member_ptr_t ptr) : m_name(name), m_ptr(ptr) {};
		const T& Get(const Class& obj) const;

	private:
		const char* m_name;
		member_ptr_t m_ptr;
	};
};

#include "SerializableField.inl"