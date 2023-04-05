#include "EnemyComponent.h"

#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Core/Events.h>

#include "../../Managers/GameManager.h"
#include "../Actor/RPGComponent.h"
#include "../../Core/EventData.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include "States/ChaseTargetState.h"
namespace Game
{
  EnemyComponent::EnemyComponent(Engine::GameObject& obj)
    : IComponent(obj)
    , m_stateMachine(Owner)
  {
    SetRequiredComponents<RPGComponent, ActorComponent>();
  }

  void EnemyComponent::OnDestroy()
  {
    // check if destroyed because of HP
    if (Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
    {
      // experience orb
      ExperienceGlobeDef experienceGlobeDef;
      experienceGlobeDef.Position = Owner.GetTransform()->GetPosition();

      auto* expOrb = GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef);

      // scatter

			BulletFactoryDef def;
			def.Position = Owner.GetTransform()->GetPosition();
			def.Damage = 2;
			def.BulletHits = 1;

      auto enemies = Engine::GameObjectManager::Get().GetGameObjectsByTag(Engine::GameObjectTag::ENEMY);

			for (auto& enemy : enemies)
			{
				def.Rotation = Engine::math::AngleBetweenVecs(Owner.GetTransform()->GetPosition(), enemy->GetTransform()->GetPosition());
			  GameObjectFactory::CreateBulletObject(def);
			}
      // event
      event::E_EnemyDied eventData;
      Engine::EventManager::Get().DispatchEvent<event::E_EnemyDied>(eventData);
    }
  }

	void EnemyComponent::Update(float dt)
	{
    m_stateMachine.Update(dt);
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