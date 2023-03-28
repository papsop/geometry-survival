#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Application.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/ImGui/imgui.h>

#include "../Skills/ISkill.h"

#include <vector>
#include <memory>
namespace Game
{
  class SkillsManager : public Engine::IManager, public Engine::IDebuggable
  {
  public:
    SkillsManager(Engine::Application& app);
    ~SkillsManager() = default;

    std::vector< ISkill* > GetNRandomSkills(int N);


    void Debug(Engine::view::IViewStrategy* viewStrategy) override;

  protected:
		void VirtualOnInit() override;
    void VirtualOnDestroy() override;

  private:
    void ResetToDefaultSkills();

    Engine::Application& m_app;
    std::vector< std::unique_ptr<ISkill> > m_availableSkills;
    int m_selectedSkill = 0;

  };
}