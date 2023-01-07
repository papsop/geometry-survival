#include "EnemyComponent.h"

#include <Engine/Managers/EventManager.h>
#include <Engine/Core/Events.h>
#include "../Actor/RPGComponent.h"
#include "../../Core/EventData.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{
  EnemyComponent::EnemyComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
    SetRequiredComponents<RPGComponent>();
  }

  void EnemyComponent::OnDestroy()
  {
    // check if destroyed because of HP
    if (Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
    {
      ExperienceGlobeDef experienceGlobeDef;
      experienceGlobeDef.Position = Owner.GetTransform()->GetPosition();

      auto* expOrb = GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef);

      event::E_EnemyDied eventData;
      Engine::EventManager::Get().DispatchEvent<event::E_EnemyDied>(eventData);
    }
  }

}