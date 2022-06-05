#include "IComponent.h"

namespace Engine
{
	template<typename T>
	struct IComponent::requires_impl<T>
	{
		static void check(const GameObject& obj)
		{
			bool hasComponent = obj.HasComponent<T>();
			DD_ASSERT(hasComponent, "[%s] RequiredComponents asserted, missing component '%s'", obj.DebugName, typeid(T).name());
		}
	};

	template<typename T, typename... Ts>
	struct IComponent::requires_impl<T, Ts...>
	{
		static void check(const GameObject& obj)
		{
			requires_impl<T>::check(obj);
			requires_impl<Ts...>::check(obj);
		}
	};

	template<typename... Ts>
	void IComponent::SetRequiredComponents()
	{
		m_requiredFunction = std::bind(&IComponent::requires_impl<Ts...>::check, std::placeholders::_1);
		CheckRequiredComponents();
	}

};