#include "DestroyAfterTimeComponent.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
	DestroyAfterTimeComponent::DestroyAfterTimeComponent(Engine::GameObject& owner, float timeToDie)
		: IComponent(owner)
		, m_timeToDie(timeToDie)
	{
	}

	void DestroyAfterTimeComponent::VirtualOnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	DestroyAfterTimeComponent::~DestroyAfterTimeComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void DestroyAfterTimeComponent::VirtualOnActivated()
	{
		IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void DestroyAfterTimeComponent::VirtualOnDeactivated()
	{
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

	void DestroyAfterTimeComponent::Update(float dt)
	{
		m_timeToDie -= dt;
		if (m_timeToDie <= 0.0f)
			Owner.Destroy();
	}

	void DestroyAfterTimeComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
	}

}