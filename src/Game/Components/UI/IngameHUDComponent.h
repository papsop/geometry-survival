#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/StateMachines/UIStateMachine.h"

namespace Game
{
  class IngameHUDComponent : public Engine::IUIComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    IngameHUDComponent(Engine::GameObject& obj);
    ~IngameHUDComponent() override = default;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;
    void RegisterUIElements() override;

    void UIShown() override;
    void UIHidden() override;

  private:
    UIStateMachine m_stateMachine;
    tgui::Label::Ptr m_label;
  };
}