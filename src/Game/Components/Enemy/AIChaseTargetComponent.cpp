#include "AIChaseTargetComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Core/GameObject/GameObjectTag.h>
#include <Engine/Core/Scene/Scene.h>

#include "../Actor/ActorComponent.h"
#include "../States/Actor.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{

	AIChaseTargetComponent::AIChaseTargetComponent(Engine::GameObject& obj, Engine::GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		SetRequiredComponents<ActorComponent>();
	}

	void AIChaseTargetComponent::OnCreate()
	{
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		m_stateMachine.AddState<Actor_ChaseTarget>(actorComponent, m_target);
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	AIChaseTargetComponent::~AIChaseTargetComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void AIChaseTargetComponent::Update(float dt)
	{
		m_stateMachine.Update(dt);
	}

	void AIChaseTargetComponent::ProcessMessage(const Engine::Message& message)
	{
	}

	void AIChaseTargetComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		auto otherGO = collision.Other;
		// check if player bullet
		if (otherGO->Tag != Engine::GameObjectTag::PLAYER_BULLET)
			return;

		// apply knockback
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		Engine::math::Vec2 knockBackDirection = Engine::math::V2fNormalize(Owner.GetTransform()->GetPosition() - otherGO->GetTransform()->GetPosition());
		actorComponent->AddCommand<KnockBackCommand>(knockBackDirection.x, knockBackDirection.y);
		
		// go to stun
		m_stateMachine.AddState<Actor_Stunned>(actorComponent, 1.0f);
	}

	void AIChaseTargetComponent::OnDestroy()
	{
		// check if destroyed because of HP
		if (Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
		{
			ExperienceGlobeDef experienceGlobeDef;
			experienceGlobeDef.Position = Owner.GetTransform()->GetPosition();

			auto* expOrb = GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef);
			//Owner.GetScene().AddGameObject(GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef)->ID);
		}
	}

}


