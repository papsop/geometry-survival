#include "GameObject.h"

namespace Engine
{
	template<typename T, typename>
	bool GameObject::HasComponent() const
	{
		auto compID = IdGenerator<IComponent>::GetID<T>();
		return m_components.find(compID) != m_components.end();
	}

	template<typename T, typename ... Args, typename>
	void GameObject::AddComponent(Args&& ... args)
	{
		if (!HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			m_components[ID] = std::make_unique<T>(*this, std::forward<Args>(args) ...);
			m_components[ID]->OnCreate();
		}
		else LOG_WARN("AddComponent: GO %d already has Component '%s', ignoring this function call", ID, typeid(T).name());
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
};