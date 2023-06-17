#include "ComponentManager.h"

#include "../Application.h"
#include "../Core/GameObject/GameObject.h"

namespace Engine
{

	ComponentManager& ComponentManager::Get()
	{
		return Application::Instance().GetComponentManager();
	}


	void ComponentManager::Update(float dt)
	{
		Lock();
		for (auto& container : m_containers)
			container.second->Update(dt);
		Unlock();
	}

	void ComponentManager::FixedUpdate(float dt)
	{
		Lock();
		for (auto& container : m_containers)
			container.second->FixedUpdate(dt);
		Unlock();
	}

	// CONTAINER
	
	void ComponentsContainer::RegisterComponent(IComponent* component)
	{
		// Lock is ensured in ComponentManager
		m_components.emplace_back(component);
	}

	void ComponentsContainer::UnregisterComponent(IComponent* component)
	{
		// Lock is ensured in ComponentManager
		m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
	}

	void ComponentsContainer::IterateOverComponents(TComponentEnumerate func)
	{
		for (auto& component : m_components)
		{
			func(component);
		}
	}

	void ComponentsContainer::Update(float dt)
	{
		IterateOverComponents(
			[&](IComponent* c)
			{
				if (c->ShouldUpdate())
					c->Update(dt);
			}
		);
	}

	void ComponentsContainer::FixedUpdate(float dt)
	{
		IterateOverComponents(
			[&](IComponent* c)
			{
				if (c->ShouldUpdate())
					c->FixedUpdate(dt);
			}
		);
	}

};