#include "ComponentManager.h"
#include "../Utils/IdGenerator.h"

namespace Engine
{
	template<typename T, typename>
	void ComponentManager::RegisterComponentType()
	{
		auto ID = IdGenerator<ComponentManager>::GetID<T>();
		if (m_containers.find(ID) != m_containers.end())
		{
			LOG_WARN("component '%s' already registered", typeid(T).name());
			return;
		}
		else
		{
			m_containers.emplace(ID, std::make_unique<ComponentsContainer>(ID));
			LOG_DEBUG("Registered component type '%s'", typeid(T).name());
		}
	}

	template<typename T, typename>
	void ComponentManager::RegisterComponent(T* component)
	{
		auto ID = IdGenerator<ComponentManager>::GetID<T>();
		DD_ASSERT(m_containers.find(ID) != m_containers.end(), "ComponentContainer for this component doesn't exist");
		LOG_DEBUG("Registered component '%s'", typeid(T).name());
		m_containers[ID]->RegisterComponent(component);
	}

	template<typename T, typename>
	void ComponentManager::UnregisterComponent(T* component)
	{
		auto ID = IdGenerator<ComponentManager>::GetID<T>();
		DD_ASSERT(m_containers.find(ID) != m_containers.end(), "ComponentContainer for this component doesn't exist");
		LOG_DEBUG("Unregistered component '%s'", typeid(T).name());
		m_containers[ID]->UnregisterComponent(component);
	}

	template<typename T, typename>
	std::vector<T*> ComponentManager::GetComponentsContainer()
	{
		auto ID = IdGenerator<ComponentManager>::GetID<T>();
		DD_ASSERT(m_containers.find(ID) != m_containers.end(), "ComponentContainer for this component doesn't exist");
		return m_containers[ID];
	}
};