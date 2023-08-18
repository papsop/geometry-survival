#include "BulletComponent.h"
#include "ActorComponent.h"

#include "../../Physics/Filters.h"
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/ComponentManager.h>

#include "../../Core/RPG/BurningBuff.h"
namespace Game
{

  BulletComponent::BulletComponent(Engine::GameObject& obj, const BulletDef& def)
    : IComponent(obj)
    , m_damage(def.Damage)
    , m_burningDamage(def.BurningDamage)
    , m_hitsLeft(def.BulletHits)
  {
    SetRequiredComponents<Engine::PhysicsBodyComponent>();
  }

	void BulletComponent::VirtualOnCreate()
	{
		m_physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
	}

	void BulletComponent::VirtualOnActivated()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	void BulletComponent::VirtualOnDeactivated()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void BulletComponent::Update(float dt)
	{
    m_physBody->SetLinearVelocity(50.0f);
	}

	void BulletComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
	}

	void BulletComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
    auto otherActor = collision.Other->GetComponent<ActorComponent>();
    if (otherActor == nullptr) return;
    if (collision.MyFilter.categoryBits != physics::EntityCategory::PLAYER_BULLET) return;
    if (m_collisions.find(otherActor->Owner.ID) != m_collisions.end()) return;

    // Flat damage
    m_collisions.insert(otherActor->Owner.ID);
    otherActor->AddCommand<DamageCommand>(m_damage, m_owner, Actor_DamageType::Bullet);
    
    // Burning
    auto* otherRPGComponent = collision.Other->GetComponent<RPGComponent>();
    if (m_burningDamage && otherRPGComponent)
    {
      auto buff = std::make_unique<BurningBuff>(3.0f, m_burningDamage, Buff::BuffTag::Burning);
      buff->AddPercentageModifier(RPGStats::MOVEMENT_SPEED, -0.5f);
      otherRPGComponent->AddBuff(std::move(buff));
    }

    // =========
    m_hitsLeft--;
    if(m_hitsLeft<= 0) Owner.Destroy();
	}

	void BulletComponent::SetDamage(float damage)
	{
    m_damage = damage;
	}

	void BulletComponent::SetHitsLeft(int hitsLeft)
	{
    m_hitsLeft = hitsLeft;
	}

}