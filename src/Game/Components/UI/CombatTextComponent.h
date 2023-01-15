#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class CombatTextComponent : public Engine::IUIComponent
  {
  public:
    struct CombatTextDef
    {
      std::string Value;
      float Duration;
      Engine::math::Vec2 Position;
    };

    CombatTextComponent(Engine::GameObject& obj);
    ~CombatTextComponent() override = default;

    void AddCombatTextEntry(CombatTextDef def);

  protected:
    void RegisterUIElements() override;
    void UIShown() override;
    void UIHidden() override;
    void Update(float dt) override;

  private:
    struct CombatTextEntry
    {
      CombatTextDef Def;
      tgui::Label::Ptr LabelPtr = nullptr;
    };

    std::vector<CombatTextEntry> m_entries;
  };
}