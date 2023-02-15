#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Application.h>
#include "../Skills/ISkill.h"

#include <vector>
#include <memory>
namespace Game
{
  class SkillsManager : public Engine::IManager
  {
  public:
    SkillsManager(Engine::Application& app);
    ~SkillsManager() = default;

    std::vector< ISkill* > GetNRandomSkills(int N);

  protected:
    void VirtualOnInit() override;

  private:
    void ResetToDefaultSkills();

    Engine::Application& m_app;
    std::vector< std::unique_ptr<ISkill> > m_availableSkills;

  };
}