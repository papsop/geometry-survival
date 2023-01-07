#include "Skill_AmmoStealer.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{

  Skill_AmmoStealer::Skill_AmmoStealer()
    : ISkill("Ammo stealer", "Upon killing an enemy, you receive +1 ammo back")
  {
  }

  void Skill_AmmoStealer::Learn(Engine::GameObject* entity)
  {
    // using BuffTag::None so we can stack this buff instead of overwriting
    auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
    skillBuff->AddAdditiveModifier(RPGStats::AMMO_ON_KILL, 1);

    auto* rpg = entity->GetComponent<RPGComponent>();

    if (rpg)
    {
      rpg->AddBuff(std::move(skillBuff));
    }

    LOG_INFO("Learning AmmoStealer");
  }

}