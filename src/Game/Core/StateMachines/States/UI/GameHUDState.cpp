#include "GameHUDState.h"
#include "GameMenuState.h"
#include "../../UIStateMachine.h"

namespace Game
{

  void GameHUDState::OnCreate()
  {
    
  }

  void GameHUDState::OnDestroy()
  {
    
  }

  void GameHUDState::OnEscapeAction()
  {
    m_stateMachine->SetState(new GameMenuState());
  }
}