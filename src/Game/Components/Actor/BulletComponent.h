#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
  struct BulletDef {
    float Damage;
    int   BulletHits;
       
    // burning effect
    float BurningDamage = 0.0f; // per second
  };

  class BulletComponent : public Engine::IComponent
  {
  public:
    BulletComponent(Engine::GameObject& obj, const BulletDef& def);
    ~BulletComponent();

    void OnCreate() override;
    void Update(float dt) override;

    void OnCollisionStart(Engine::CollisionData& collision) override;

  private:
    float m_timeToDie = 3.0f;
    float m_damage;
    float m_burningDamage;
    int m_hitsLeft = 2;
    std::set<Engine::GameObjectID> m_collisions;
  };
}

