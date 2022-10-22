#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/StateMachines/UIStateMachine.h"

namespace Game
{
  class IngameUIComponent : public Engine::IComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    IngameUIComponent(Engine::GameObject& obj);
    ~IngameUIComponent() override = default;

    void OnCreate() override;
    void OnDestroy() override;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    UIStateMachine m_stateMachine;
  };
}