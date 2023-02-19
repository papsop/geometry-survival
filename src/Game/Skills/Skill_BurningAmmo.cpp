#include "Skill_BurningAmmo.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{
  Skill_BurningAmmo::Skill_BurningAmmo()
    : ISkill("+2 burning damage", "")
  {
  }

  void Skill_BurningAmmo::Learn(Engine::GameObject* entity)
  {
    // using BuffTag::None so we can stack this buff instead of overwriting
    auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
    skillBuff->AddAdditiveModifier(RPGStats::BURNING_DAMAGE, 2);

    auto* rpg = entity->GetComponent<RPGComponent>();

    if (rpg)
    {
      rpg->AddBuff(std::move(skillBuff));
    }

    LOG_INFO("Learning BurningDamage");
  }

}