#pragma once
#include "States/UI/UIState.h"
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include <memory>

namespace Game
{

  class UIStateMachine : public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    UIStateMachine() = default;
    ~UIStateMachine();

    void SetState(UIState* state);
    UIState* GetState();

    void OnEscapeAction();

    void PauseGame();
    void UnpauseGame();

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

  private:
    std::unique_ptr<UIState> m_currentState;
  
  };

}