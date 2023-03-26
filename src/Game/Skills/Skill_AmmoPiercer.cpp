#include "Skill_AmmoPiercer.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{

  Skill_AmmoPiercer::Skill_AmmoPiercer()
    : ISkill("AmmoPiercer", "+1 Ammo piercing")
  {
  }

  void Skill_AmmoPiercer::Learn(Engine::GameObject* entity)
  {
    // using BuffTag::None so we can stack this buff instead of overwriting
    auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
    skillBuff->AddAdditiveModifier(RPGStats::AMMO_HITS, 1);

    auto* rpg = entity->GetComponent<RPGComponent>();

    if (rpg)
    {
      rpg->AddBuff(std::move(skillBuff));
    }

    LOG_INFO("Learning AmmoPiercer");
  }

}