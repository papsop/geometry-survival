#include "GameObject.h"
namespace Engine
{
	template<typename T, typename>
	bool GameObject::HasComponent() const
	{
		return m_components.find(IdGenerator<IComponent>::GetID<T>()) != m_components.end();
	}

	template<typename T, typename ... Args, typename>
	void GameObject::AddComponent(Args&& ... args)
	{
		if (!HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			m_components[ID] = std::make_unique<T>(*this, std::forward<Args>(args) ...);
		}
		else
			LOG_WARN("AddComponent: GO %d already has Component '%s', ignoring this function call", ID, typeid(T).name());
	}

	template<typename T, typename>
	void GameObject::RemoveComponent()
	{
		if (HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			m_components.erase(ID);
		}

		for (auto& component : m_components)
			component.second->CheckRequiredComponents();
	}

	template<typename T, typename>
	T* GameObject::GetComponent()
	{
		if (HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			return dynamic_cast<T*>(m_components[ID].get());
		}
		else
			return nullptr;
	}

	template<typename T, typename>
	T* GameObject::GetTransformAs()
	{
		return dynamic_cast<T*>(m_transform.get());
	}
};