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

    // todo: nicer?
    tgui::Button::Ptr m_skillButtons[3];

    // Fake experience bar, because HUD is hidden right now
    tgui::Panel::Ptr m_experienceBar;
  };
}