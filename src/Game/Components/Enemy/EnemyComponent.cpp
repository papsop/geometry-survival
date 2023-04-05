#include "EnemyComponent.h"
#include "ScatterFieldComponent.h"

#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Core/Events.h>

#include "../Actor/RPGComponent.h"
#include "../../Core/EventData.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include "States/TestEnemyState.h"
namespace Game
{
  EnemyComponent::EnemyComponent(Engine::GameObject& obj)
    : IComponent(obj)
    , m_stateMachine(Owner)
  {
    SetRequiredComponents<RPGComponent>();

    m_stateMachine.AddState<TestEnemyState>();

    m_stateMachine.Update(0.0f);
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

}