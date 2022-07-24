#pragma once
#include <Engine/Core/StateMachine/IState.h>
#include "../Actor/ActorComponent.h"

namespace Game
{
	class Actor_ChaseTarget : public Engine::IState
	{
	public:
		Actor_ChaseTarget(Engine::FiniteStateMachine& parentStateMachine, ActorComponent* actorComponent, Engine::GameObject* target);
		~Actor_ChaseTarget() = default;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;
		void OnTransitionOut() override;

	private:
		ActorComponent* m_parentActor;
		Engine::GameObject* m_target;
	};
}