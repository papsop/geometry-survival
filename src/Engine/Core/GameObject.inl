#include "GameObject.h"

namespace Engine
{
	template<typename T>
	bool GameObject::HasComponent() const
	{
		static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
		auto compID = IdGenerator<IComponent>::GetID<T>();
		return m_components.find(compID) != m_components.end();
	}

	template<typename T, typename ... Args>
	void GameObject::AddComponent(Args&& ... args)
	{
		static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
		if (!HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			m_components[ID] = std::make_unique<T>(*this, std::forward<Args>(args) ...);
			m_components[ID]->OnCreate();
		}
		else LOG_WARN("AddComponent: GO %d already has Component '%s', ignoring this function call", c_ID, typeid(T).name());
	}

	template<typename T>
	void GameObject::RemoveComponent()
	{
		// TODO: add required check for each component that remained on the gameobject
		static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
		if (HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			m_components.erase(ID);
		}

		for (auto& component : m_components)
			component.second->CheckRequiredComponents();
	}

	template<typename T>
	T* GameObject::GetComponent()
	{
		static_assert(std::is_base_of<IComponent, T>::value, "Not derived from IComponent");
		if (HasComponent<T>())
		{
			auto ID = IdGenerator<IComponent>::GetID<T>();
			return dynamic_cast<T*>(m_components[ID].get());
		}
		else
			return nullptr;
	}
};