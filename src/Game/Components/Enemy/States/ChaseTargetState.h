#pragma once
#include "../EnemyComponent.h"
#include "../../Actor/ActorComponent.h"

namespace Game
{
	class ChaseTargetState : public Engine::IState<EnemyAIStates>
	{
	public:
		ChaseTargetState(Engine::GameObject& owner, Engine::IState<EnemyAIStates>::StateMachine& sm);
		~ChaseTargetState() override = default;

		void Update(float dt) override;
		void OnTransitionIn() override;
	private:
		ActorComponent* m_actorComponent;
		Engine::GameObject* m_target;
	};
}