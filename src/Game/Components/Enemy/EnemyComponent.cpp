#include "EnemyComponent.h"

#include <algorithm>

#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/Events.h>

#include "../../Managers/GameManager.h"
#include "../Actor/RPGComponent.h"
#include "../../Core/EventData.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include "States/ChaseTargetState.h"
#include "States/EnemyStunnedState.h"

namespace Game
{
  EnemyComponent::EnemyComponent(Engine::GameObject& obj)
    : IComponent(obj)
    , m_stateMachine(Owner)
  {
    SetRequiredComponents<RPGComponent, ActorComponent, Engine::SpriteDrawableComponent>();
  }

	void EnemyComponent::OnCreate()
	{
		Owner.GetComponent<ActorComponent>()->OnZeroHealth.AddListener(this, &EnemyComponent::OnDeath);
		m_spriteDrawableComponent = Owner.GetComponent<Engine::SpriteDrawableComponent>();
	}

	void EnemyComponent::OnDestroy()
	{
		Owner.GetComponent<ActorComponent>()->OnZeroHealth.RemoveListener(this);
  }

	void EnemyComponent::Update(float dt)
	{
    m_stateMachine.Update(dt);

		if (!m_target)
			return;

		// continuous damage to the target
		if (m_isTouchingTarget && m_stateMachine.GetActiveState()->GetStateValue() == EnemyAIStates::CHASING)
			m_target->GetComponent<ActorComponent>()->ApplyDamage(5 * dt, Actor_DamageSource::Collision);

	}

	void EnemyComponent::OnDeath()
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

		Owner.Destroy();
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

	void EnemyComponent::VirtualOnActivated()
	{
		m_target = GameManager::Get()->GetPlayerGameObject();
		Engine::ComponentManager::Get().RegisterComponent(this);
		Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
		m_stateMachine.AddState<ChaseTargetState>();
	}

	void EnemyComponent::VirtualOnDeactivated()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
		Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		m_stateMachine.Clear();
	}

	void EnemyComponent::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData)
	{
		m_target = eventData.PlayerObject;
	}

}