#include "CombatTextComponent.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

	CombatTextComponent::CombatTextComponent(Engine::GameObject& obj, float duration)
		: IComponent(obj)
		, m_durationLeft(duration)
	{

	}

	void CombatTextComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	void CombatTextComponent::OnDestroy()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void CombatTextComponent::Update(float dt)
	{
		m_durationLeft -= dt;

		if (m_durationLeft < 0)
		{
			Owner.Destroy();
		}
	}



}