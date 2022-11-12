#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>

namespace Game
{
  class SkillPickerScreenComponent : public Engine::IUIComponent
  {
  public:
    SkillPickerScreenComponent(Engine::GameObject& obj);
    ~SkillPickerScreenComponent() override = default;

  protected:
    void RegisterUIElements() override;

    void UIShown() override;
    void UIHidden() override;

  private:
    void ReturnToGame();
    void PickSkillNumber(size_t index);

    tgui::HorizontalLayout::Ptr m_layout;

    // todo: nicer? config or something
    static const size_t m_numberOfSkills = 3;
    
    tgui::Button::Ptr m_skillButtons[m_numberOfSkills];


    // Fake experience bar, because HUD is hidden right now
    tgui::Panel::Ptr m_experienceBar;
  };
}