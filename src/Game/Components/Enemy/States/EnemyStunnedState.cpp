#include "EnemyStunnedState.h"
#include "../../Actor/ActorComponent.h"

#include <Engine/Core/StateMachine/PushdownStateMachine.h>

namespace Game
{
	EnemyStunnedState::EnemyStunnedState(Engine::GameObject& owner, Engine::IState<EnemyAIStates>::StateMachine& sm, float duration)
		: IState(owner, sm, EnemyAIStates::STUNNED)
		, m_duration(duration)
	{

	}

	void EnemyStunnedState::OnTransitionIn()
	{
		m_parentGameObject.GetComponent<ActorComponent>()->AddCommand<MoveCommand>(0.0f,0.0f);
		
		//m_previousColor = m_shapeViewComponent->GetRenderable().shape.Color;
		//m_shapeViewComponent->GetMutableRenderable().shape.Color = sf::Color::White;
	}

	void EnemyStunnedState::OnTransitionOut()
	{
		//m_shapeViewComponent->GetMutableRenderable().shape.Color = m_previousColor;
	}

	void EnemyStunnedState::Update(float dt)
	{
		m_duration -= dt;
		if (m_duration <= 0.0f)
			m_parentStateMachine.PopState();
	}
}
