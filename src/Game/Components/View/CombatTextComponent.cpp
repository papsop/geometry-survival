#include "CombatTextComponent.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

	CombatTextComponent::CombatTextComponent(Engine::GameObject& obj, float duration)
		: IComponent(obj)
		, m_initialDuration(duration)
		, m_durationLeft(duration)
	{

	}

	void CombatTextComponent::VirtualOnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	void CombatTextComponent::OnDestroy()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void CombatTextComponent::VirtualOnActivated()
	{
		IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void CombatTextComponent::VirtualOnDeactivated()
	{
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

	void CombatTextComponent::Update(float dt)
	{
		m_durationLeft -= dt;

		auto position = Owner.GetTransform()->GetPosition();
		position.y += 10 * dt;
		Owner.GetTransform()->SetPosition(position);

		if (m_durationLeft < 0)
		{
			Owner.Destroy();
		}
	}

	void CombatTextComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
	}

}