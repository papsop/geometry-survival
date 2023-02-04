#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/EventData.h"

namespace Game
{
  class SettingsScreenComponent : public Engine::IUIComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    SettingsScreenComponent(Engine::GameObject& obj);
    ~SettingsScreenComponent() override = default;


    void BackToMenuCallback();
    void SaveSettingsCallback();
  protected:
    void RegisterUIElements() override;
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    void UIShown() override;
    void UIHidden() override;

  private:
    tgui::VerticalLayout::Ptr m_settingsLayout;

    tgui::Label::Ptr m_headerLabel;

    tgui::HorizontalLayout::Ptr m_resolutionLayout;
    tgui::Label::Ptr m_resolutionLabel;
    tgui::ComboBox::Ptr m_resolutionComboBox;

    tgui::HorizontalLayout::Ptr m_buttonsLayout;
    tgui::Button::Ptr m_saveSettingsButton;
    tgui::Button::Ptr m_backToMenuButton;

  };
}