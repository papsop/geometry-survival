#include "GameMenuComponent.h"
#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
#include "../../Core/EventData.h"

namespace Game
{

  GameMenuComponent::GameMenuComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {

  }

  void GameMenuComponent::OnCreate()
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
      m_backToMenuButton = tgui::Button::create("Back to menu");

      // quit button settings
      m_quitButton = tgui::Button::create("Quit game");

      // callbacks
      m_newGameButton->onClick(&GameMenuComponent::NewGameButtonCallback, this);
      m_settingsButton->onClick(&GameMenuComponent::SettingsButtonCallback, this);
      m_backToMenuButton->onClick(&GameMenuComponent::BackToMenuButtonCallback, this);
      m_quitButton->onClick(&GameMenuComponent::QuitButtonCallback, this);

      // add to gui
      m_menuLayout->add(m_newGameButton);
      m_menuLayout->add(m_settingsButton);
      m_menuLayout->add(m_backToMenuButton);
      m_menuLayout->add(m_quitButton);

      m_newGameButton->setVisible(false);
      m_settingsButton->setVisible(false);
      m_backToMenuButton->setVisible(false);
      m_quitButton->setVisible(false);
      m_menuLayout->setVisible(false);

      gui->add(m_menuLayout);
    }
  }

  void GameMenuComponent::OnDestroy()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (gui)
    {
      gui->remove(m_quitButton);
      gui->remove(m_menuLayout);
    }
  }

  void GameMenuComponent::VirtualOnActivated()
  {
    m_newGameButton->setVisible(true);
    m_settingsButton->setVisible(true);
    m_backToMenuButton->setVisible(true);
    m_quitButton->setVisible(true);
    m_menuLayout->setVisible(true);
    SendMainMenuEvent();
  }

  void GameMenuComponent::VirtualOnDeactivated()
  {
    m_newGameButton->setVisible(false);
    m_settingsButton->setVisible(false);
    m_backToMenuButton->setVisible(false);
    m_quitButton->setVisible(false);
    m_menuLayout->setVisible(false);
    SendMainMenuEvent();
  }

  void GameMenuComponent::SendMainMenuEvent()
  {
//     event::E_OnGameMenu event;
//     event.IsActive = IsActive();
//     Engine::EventManager::Get().DispatchEvent(event);
  }

  void GameMenuComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    Owner.SetActive( ! IsActive() );
  }


  // ============= Button callbacks =============
  void GameMenuComponent::NewGameButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

  void GameMenuComponent::SettingsButtonCallback()
  {

  }

  void GameMenuComponent::BackToMenuButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
  }

  void GameMenuComponent::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }

}