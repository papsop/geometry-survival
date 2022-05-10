#include "SerializableField.h"
#include <tuple>

namespace Engine
{
	template<typename... Args>
	auto Fields(Args&&... args)
	{
		return std::make_tuple(std::forward<Args>(args)...);
	}

	template<typename Class, typename T>
	const T& SerializableField<Class, T>::Get(const Class& obj) const
	{
		return obj.*m_ptr;
	}
}