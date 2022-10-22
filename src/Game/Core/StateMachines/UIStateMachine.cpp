#include "UIStateMachine.h"
#include "../../Managers/GameManager.h"

#include <Engine/Application.h>
namespace Game
{
  UIStateMachine::~UIStateMachine()
  {
    if (m_currentState)
    {
      m_currentState->OnDestroy();
      m_currentState = nullptr;
    }
  }

  void UIStateMachine::SetState(UIState* state)
  {
    if (m_currentState)
    {
      m_currentState->OnDestroy();
    }

    m_currentState = std::unique_ptr<UIState>(state);
    m_currentState->SetParentStateMachine(this);
    m_currentState->OnCreate();
  }

  UIState* UIStateMachine::GetState()
  {
    return m_currentState.get();
  }

  void UIStateMachine::OnEscapeAction()
  {
    if (m_currentState)
    {
      m_currentState->OnEscapeAction();
    }
  }

  void UIStateMachine::PauseGame()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Paused);
  }

  void UIStateMachine::UnpauseGame()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Gameplay);
  }

  void UIStateMachine::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    if (m_currentState)
    {
      m_currentState->OnEscapeAction();
    }
  }

}
