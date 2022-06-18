#include "Actor_ChaseTarget.h"
#include <Engine/Debug/Logger.h>

namespace Game
{

	Actor_ChaseTarget::Actor_ChaseTarget(ActorComponent* actorComponent, Engine::GameObject* target)
		: m_parentActor(actorComponent)
		, m_target(target)
	{

	}

	void Actor_ChaseTarget::OnInit()
	{
		
	}

	void Actor_ChaseTarget::OnDestroy()
	{
		
	}

	void Actor_ChaseTarget::Update(float dt)
	{
		// chase
		Engine::math::Vec2 meToTarget = Engine::math::V2fNormalize(m_target->GetTransform().Position - m_parentActor->Owner.GetTransform().Position);
		m_parentActor->AddCommand(std::make_unique<MoveCommand>(meToTarget.x * 0.5f, meToTarget.y * 0.5f));

		// rotate
		float angle = Engine::math::AngleBetweenVecs(m_parentActor->Owner.GetTransform().Position, m_target->GetTransform().Position);
		m_parentActor->AddCommand(std::make_unique<RotateCommand>(angle));
	}

	void Actor_ChaseTarget::ProcessMessage(const Engine::Message& message)
	{
		LOG_WARN("Received message");
	}
};
