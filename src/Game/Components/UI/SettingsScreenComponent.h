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
  protected:
    void RegisterUIElements() override;
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    void UIShown() override;
    void UIHidden() override;

  private:
    tgui::VerticalLayout::Ptr m_menuLayout;

    tgui::Label::Ptr m_menuLabel;
    tgui::Button::Ptr m_backToMenuButton;

  };
}