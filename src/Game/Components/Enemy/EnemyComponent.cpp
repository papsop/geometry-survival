#include "EnemyComponent.h"

#include <algorithm>

#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Components/Physics/PhysicsBodyComponent.h>
#include <Engine/Components/Drawables/AnimationControllerComponent.h>
#include <Engine/Application.h>
#include <Engine/Core/Events.h>

#include "../../Managers/GameManager.h"
#include "../Actor/RPGComponent.h"
#include "../../Core/EventData.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include "States/ChaseTargetState.h"
#include "States/EnemyStunnedState.h"

namespace Game
{
  EnemyComponent::EnemyComponent(Engine::GameObject& obj, EnemyComponentDef def)
    : IComponent(obj)
    , m_stateMachine(Owner)
		, m_damagePerSecond(def.DamagePerSecond)
  {
    SetRequiredComponents<RPGComponent, ActorComponent, Engine::SpriteDrawableComponent>();
  }

	void EnemyComponent::VirtualOnCreate()
	{
		Owner.GetComponent<ActorComponent>()->OnZeroHealth.AddListener(this, &EnemyComponent::OnZeroHealthCallback);
		m_spriteDrawableComponent = Owner.GetComponent<Engine::SpriteDrawableComponent>();
	}

	void EnemyComponent::OnDestroy()
	{
		Owner.GetComponent<ActorComponent>()->OnZeroHealth.RemoveListener(this);
  }

	void EnemyComponent::Update(float dt)
	{
		if (m_isDying)
			return;

    m_stateMachine.Update(dt);

		if (!m_target)
			return;

		// continuous damage to the target
		if (m_isTouchingTarget && m_stateMachine.GetActiveState()->GetStateValue() == EnemyAIStates::CHASING)
			m_target->GetComponent<ActorComponent>()->ApplyDamage(m_damagePerSecond * dt, Actor_DamageSource::Collision);

	}

	void EnemyComponent::OnZeroHealthCallback()
	{
		// this bool controls animatorcontroller death state
		m_isDying = true;
		Owner.GetComponent<Engine::PhysicsBodyComponent>()->SetEnabled(false);
	}

	void EnemyComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		if(collision.Other->Tag == Engine::GameObjectTag::PLAYER_BULLET)
			m_stateMachine.AddState<EnemyStunnedState>(1.0f);

		if (collision.Other->Tag == Engine::GameObjectTag::PLAYER)
			m_isTouchingTarget = true;
	}

	void EnemyComponent::OnCollisionEnd(Engine::CollisionData& collision)
	{
		// !collision.Other is for case when player is already dead, but we still have to receive onCollisionEnd
		if (!collision.Other || collision.Other->Tag == Engine::GameObjectTag::PLAYER)
			m_isTouchingTarget = false;
	}

	void EnemyComponent::OnDeathAnimationFinishedCallback()
	{
		LOG_INFO("OnDeathAnimationFinishedCallback");
		OnDeathImpl();
	}

	void EnemyComponent::VirtualOnActivated()
	{
		m_target = GameManager::Get()->GetPlayerGameObject();
		Engine::ComponentManager::Get().RegisterComponent(this);
    Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
    Engine::IEventListener<event::E_GameStateChanged>::RegisterListener();
		m_stateMachine.AddState<ChaseTargetState>();
	}

	void EnemyComponent::VirtualOnDeactivated()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
		Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		Engine::IEventListener<event::E_GameStateChanged>::UnregisterListener();
		m_stateMachine.Clear();
	}

	void EnemyComponent::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData)
	{
		m_target = eventData.PlayerObject;
	}

  void EnemyComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
  {
		SetEnabled(eventData.NewState == GameState::Gameplay);
  }

	void EnemyComponent::OnDeathImpl()
	{
		// experience orb
		ExperienceGlobeDef experienceGlobeDef;
		experienceGlobeDef.Position = Owner.GetTransform()->GetPosition();

		GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef);

		// scatter
		if (m_target)
		{
			float scatters = m_target->GetComponent<RPGComponent>()->GetStat(RPGStats::SCATTERS);
			if (scatters > 0.0f)
			{
				BulletFactoryDef def;
				def.Position = Owner.GetTransform()->GetPosition();
				def.Damage = 2;
				def.BulletHits = 1;

				auto enemies = Engine::GameObjectManager::Get().GetGameObjectsByTag(Engine::GameObjectTag::ENEMY);

				for (int i = 0; i < std::min(static_cast<size_t>(scatters), enemies.size()); i++)
				{
					def.Rotation = Engine::math::AngleBetweenVecs(Owner.GetTransform()->GetPosition(), enemies[i]->GetTransform()->GetPosition());
					GameObjectFactory::CreateBulletObject(def);
				}
			}
		}

		// event about death
		event::E_EnemyDied eventData;
		Engine::EventManager::Get().DispatchEvent<event::E_EnemyDied>(eventData);
		LOG_INFO("Calling Owner.Destroy()");
		Owner.Destroy();
	}

}