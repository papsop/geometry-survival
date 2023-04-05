#include "ChaseTargetState.h"

namespace Game
{
	ChaseTargetState::ChaseTargetState(Engine::GameObject& owner, Engine::IState<EnemyAIStates>::StateMachine& sm)
		: IState(owner, sm, EnemyAIStates::CHASING)
	{

	}

	void ChaseTargetState::OnTransitionIn()
	{
		m_actorComponent = m_parentGameObject.GetComponent<ActorComponent>();
		m_target = m_parentGameObject.GetComponent<EnemyComponent>()->GetTarget();
	}

	void ChaseTargetState::Update(float dt)
	{
		m_target = m_parentGameObject.GetComponent<EnemyComponent>()->GetTarget();
		if (!m_target || !m_actorComponent)
			return;

		// chase
		Engine::math::Vec2 meToTarget = Engine::math::V2fNormalize(m_target->GetTransform()->GetPosition() - m_actorComponent->Owner.GetTransform()->GetPosition());
		m_actorComponent->AddCommand<MoveCommand>(meToTarget.x * 0.5f, meToTarget.y * 0.5f);

		// rotate
		float angle = Engine::math::AngleBetweenVecs(m_actorComponent->Owner.GetTransform()->GetPosition(), m_target->GetTransform()->GetPosition());
		m_actorComponent->AddCommand<RotateCommand>(angle);
	}
}


