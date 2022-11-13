#include "Skill_AmmoStealer.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{
  void Skill_AmmoStealer::Learn(Engine::GameObject* entity)
  {
    auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::AmmoStealer);
    skillBuff->AddAdditiveModifier(RPGStats::AMMO_ON_KILL, 1);

    auto* rpg = entity->GetComponent<RPGComponent>();

    if (rpg)
    {
      rpg->AddBuff(std::move(skillBuff));
    }

    LOG_INFO("Learning AmmoStealer");
  }

}