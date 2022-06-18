#pragma once
#include <Engine/Core/StateMachine/IState.h>
#include "../Actor/ActorComponent.h"

namespace Game
{
	// add event when player/target dies
	class Actor_ChaseTarget : public Engine::IState
	{
	public:
		Actor_ChaseTarget(ActorComponent* actorComponent, Engine::GameObject* target);
		~Actor_ChaseTarget() = default;

		void OnInit() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;

	private:
		ActorComponent* m_parentActor;
		Engine::GameObject* m_target;
	};
}