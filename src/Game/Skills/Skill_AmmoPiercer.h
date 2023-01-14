#pragma once
#include "ISkill.h"

namespace Game
{

  class Skill_AmmoPiercer : public ISkill
  {
  public:
    Skill_AmmoPiercer();
    ~Skill_AmmoPiercer() = default;

    void Learn(Engine::GameObject* entity) override;
  };
}