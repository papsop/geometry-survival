#include "AIChasePlayerComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Core/GameObject/GameObjectTag.h>
#include <Engine/Core/Scene/Scene.h>

#include "../../Physics/Filters.h"
#include "../Actor/ActorComponent.h"
#include "../States/Actor.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{

	AIChasePlayerComponent::AIChasePlayerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<ActorComponent, EnemyComponent>();
	}

	void AIChasePlayerComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);

		auto actorComponent = Owner.GetComponent<ActorComponent>();
		m_stateMachine.AddState<Actor_ChasePlayer>(actorComponent);
	}

	AIChasePlayerComponent::~AIChasePlayerComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void AIChasePlayerComponent::Update(float dt)
	{
		m_stateMachine.Update(dt);
	}

	void AIChasePlayerComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		auto otherGO = collision.Other;
		// check if player bullet
		if (collision.OtherFilter.categoryBits != physics::EntityCategory::PLAYER_BULLET)
			return;

		// apply knockback
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		Engine::math::Vec2 knockBackDirection = Engine::math::V2fNormalize(Owner.GetTransform()->GetPosition() - otherGO->GetTransform()->GetPosition());
		actorComponent->AddCommand<KnockBackCommand>(knockBackDirection.x, knockBackDirection.y);
		
		// go to stun
		m_stateMachine.AddState<Actor_Stunned>(actorComponent, 1.0f);
	}

}


