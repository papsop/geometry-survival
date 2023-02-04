#include "IngameMenuComponent.h"
#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
#include "../../Core/EventData.h"
#include "Controllers/IngameUIControllerComponent.h"

namespace Game
{

  IngameMenuComponent::IngameMenuComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {

  }

  void IngameMenuComponent::RegisterUIElements()
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
    m_newGameButton->onClick(&IngameMenuComponent::NewGameButtonCallback, this);
    m_settingsButton->onClick(&IngameMenuComponent::SettingsButtonCallback, this);
    m_backToMenuButton->onClick(&IngameMenuComponent::BackToMenuButtonCallback, this);
    m_quitButton->onClick(&IngameMenuComponent::QuitButtonCallback, this);

    // add to gui
    m_menuLayout->add(m_newGameButton);
    m_menuLayout->add(m_settingsButton);
    m_menuLayout->add(m_backToMenuButton);
    m_menuLayout->add(m_quitButton);

    m_group->add(m_menuLayout);
  }

  void IngameMenuComponent::UIShown()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Paused);
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
  }

  void IngameMenuComponent::UIHidden()
  {
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
  }

  void IngameMenuComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::HUD);
      Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Gameplay);
    } 
  }

  // ============= Button callbacks =============
  void IngameMenuComponent::NewGameButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

  void IngameMenuComponent::SettingsButtonCallback()
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::SETTINGS);
    }
  }

  void IngameMenuComponent::BackToMenuButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
  }

  void IngameMenuComponent::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }
}