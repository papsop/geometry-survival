#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"

#include <set>
namespace Game
{
  struct BulletDef {
    float Damage;
    int   BulletHits;
       
    // burning effect
    float BurningDamage = 0.0f; // per second
  };

	class BulletComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
  {
  public:
    BulletComponent(Engine::GameObject& obj, const BulletDef& def);
    ~BulletComponent();

    void OnCreate() override;
    void Update(float dt) override;

    void OnCollisionStart(Engine::CollisionData& collision) override;

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

  private:
    float m_timeToDie = 3.0f;
    float m_damage;
    float m_burningDamage;
    int m_hitsLeft = 2;
    std::set<Engine::GameObjectID> m_collisions;


  };
}

