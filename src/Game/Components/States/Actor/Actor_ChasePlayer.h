#pragma once
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Actor/ActorComponent.h"
#include "../../Enemy/EnemyComponent.h"
namespace Game
{
// 	class Actor_ChasePlayer : public Engine::IState<Engine::PushdownStateMachine>
// 	{
// 	public:
// 		Actor_ChasePlayer(Engine::PushdownStateMachine& parentStateMachine, ActorComponent* actorComponent);
// 		~Actor_ChasePlayer() = default;
// 
// 		void Update(float dt) override;
// 		void ProcessMessage(const Engine::Message& message) override;
// 
// 	private:
// 		ActorComponent* m_parentActor;
// 		Engine::GameObject* m_target;
// 	};
}