#include "BulletComponent.h"
#include "ActorComponent.h"

#include "../../Physics/Filters.h"
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

  BulletComponent::BulletComponent(Engine::GameObject& obj, const BulletDef& def)
    : IComponent(obj)
    , m_damage(def.Damage)
    , m_hitsLeft(def.BulletHits)
  {
  }

  void BulletComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
  }

  BulletComponent::~BulletComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void BulletComponent::Update(float dt)
  {
    m_timeToDie -= dt;
    if (m_timeToDie <= 0.0f)
      Owner.Destroy();
  }

	void BulletComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
    auto otherActor = collision.Other->GetComponent<ActorComponent>();
    if (otherActor == nullptr) return;
    if (collision.MyFilter.categoryBits != physics::EntityCategory::PLAYER_BULLET) return;
    if (m_collisions.find(otherActor->Owner.ID) != m_collisions.end()) return;

    m_collisions.insert(otherActor->Owner.ID);
    otherActor->AddCommand<DamageCommand>(m_damage);

    m_hitsLeft--;
    if(m_hitsLeft<= 0) Owner.Destroy();
	}

}