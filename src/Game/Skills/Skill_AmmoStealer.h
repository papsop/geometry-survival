#pragma once
#include "ISkill.h"

namespace Game
{
  
  class Skill_AmmoStealer : public ISkill
  {
  public:
    Skill_AmmoStealer() = default;
    ~Skill_AmmoStealer() = default;

    void Learn(Engine::GameObject* entity) override;
  };
}