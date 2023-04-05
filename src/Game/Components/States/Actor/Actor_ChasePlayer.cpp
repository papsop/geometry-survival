#include "Actor_ChasePlayer.h"
#include "../../../Managers/GameManager.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Application.h>

namespace Game
{

// 	Actor_ChasePlayer::Actor_ChasePlayer(Engine::PushdownStateMachine& parentStateMachine, ActorComponent* actorComponent)
// 		: IState(parentStateMachine)
// 		, m_parentActor(actorComponent)
// 	{
// 		
// 	}
// 
// 	void Actor_ChasePlayer::Update(float dt)
// 	{
// 		// todo: get player
// 		auto* target = Engine::Application::Instance().GetGameManager<GameManager>()->GetPlayerGameObject();
// 		if (target == nullptr) return;
// 
// 		// chase
// 		Engine::math::Vec2 meToTarget = Engine::math::V2fNormalize(target->GetTransform()->GetPosition() - m_parentActor->Owner.GetTransform()->GetPosition());
// 		m_parentActor->AddCommand<MoveCommand>(meToTarget.x * 0.5f, meToTarget.y * 0.5f);
// 
// 		// rotate
// 		float angle = Engine::math::AngleBetweenVecs(m_parentActor->Owner.GetTransform()->GetPosition(), target->GetTransform()->GetPosition());
// 		m_parentActor->AddCommand<RotateCommand>(angle);
// 	}
// 
// 	void Actor_ChasePlayer::ProcessMessage(const Engine::Message& message)
// 	{
// 	}

};
