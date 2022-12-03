#pragma once
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Actor/ActorComponent.h"
#include "../../Enemy/EnemyComponent.h"
namespace Game
{
	class Actor_ChaseTarget : public Engine::IState<Engine::PushdownStateMachine>
	{
	public:
		Actor_ChaseTarget(Engine::PushdownStateMachine& parentStateMachine, ActorComponent* actorComponent, Engine::GameObject* target);
		~Actor_ChaseTarget() = default;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;
		void OnTransitionOut() override;

	private:
		ActorComponent* m_parentActor;
		Engine::GameObject* m_target;
	};
}