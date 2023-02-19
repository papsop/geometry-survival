#pragma once
#include "ISkill.h"

namespace Game
{
  class Skill_BurningAmmo : public ISkill
  {
  public:
    Skill_BurningAmmo();
    ~Skill_BurningAmmo() = default;

    void Learn(Engine::GameObject* entity) override;
  };
}