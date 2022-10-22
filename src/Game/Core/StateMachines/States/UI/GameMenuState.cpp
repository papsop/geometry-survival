#include "GameMenuState.h"
#include "../../UIStateMachine.h"
#include "GameHUDState.h"

#include <Engine/Application.h>
#include "../../../../Managers/GameManager.h"

namespace Game
{

  void GameMenuState::OnCreate()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (gui)
    {
      // Layout
      m_menuLayout = tgui::VerticalLayout::create();
      m_menuLayout->setSize("30%", "45d%");
      m_menuLayout->setOrigin(0.5f, 0.0f);
      m_menuLayout->setPosition("50%", "20%");

      // New game button
      m_newGameButton = tgui::Button::create("New Game");

      // Settings button
      m_settingsButton = tgui::Button::create("Settings");

      // Back to menu button
      m_backToMenuButton = tgui::Button::create("Main menu");

      // quit button settings
      m_quitButton = tgui::Button::create("Quit game");

      // callbacks
      m_newGameButton->onClick(&GameMenuState::NewGameButtonCallback, this);
      m_settingsButton->onClick(&GameMenuState::SettingsButtonCallback, this);
      m_backToMenuButton->onClick(&GameMenuState::BackToMenuButtonCallback, this);
      m_quitButton->onClick(&GameMenuState::QuitButtonCallback, this);

      // add to gui
      m_menuLayout->add(m_newGameButton);
      m_menuLayout->add(m_settingsButton);
      m_menuLayout->add(m_backToMenuButton);
      m_menuLayout->add(m_quitButton);
      gui->add(m_menuLayout);
    }

    m_stateMachine->PauseGame();
  }

  void GameMenuState::OnDestroy()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (gui)
    {
      gui->remove(m_quitButton);
      gui->remove(m_menuLayout);
    }
  }

  void GameMenuState::OnEscapeAction()
  {
    m_stateMachine->UnpauseGame();
    m_stateMachine->SetState(new GameHUDState());
  }

  // ============================= Callbacks ============================= 
  void GameMenuState::NewGameButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

  void GameMenuState::SettingsButtonCallback()
  {

  }

  void GameMenuState::BackToMenuButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
  }

  void GameMenuState::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }

}