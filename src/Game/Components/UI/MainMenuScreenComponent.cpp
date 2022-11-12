#include "MainMenuScreenComponent.h"
#include <Engine/Application.h>
#include "../../Managers/GameManager.h"
#include <TGUI/Animation.hpp>
namespace Game
{

  MainMenuScreenComponent::MainMenuScreenComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {}

  void MainMenuScreenComponent::RegisterUIElements()
  {
    // Layout
    m_menuLayout = tgui::VerticalLayout::create();
    m_menuLayout->setSize("30%", "45%");
    m_menuLayout->setOrigin(0.5f, 0.0f);
    m_menuLayout->setPosition("50%", "20%");


    // play button settings
    m_playButton = tgui::Button::create("Play");

    m_playButton->showWithEffect(tgui::ShowEffectType::Fade, 500);

    // quit button settings
    m_quitButton = tgui::Button::create("Quit");
    m_playButton->showWithEffect(tgui::ShowEffectType::Fade, 500);

    // callbacks
    m_playButton->onClick(&MainMenuScreenComponent::PlayButtonCallback, this);
    m_quitButton->onClick(&MainMenuScreenComponent::QuitButtonCallback, this);

    // add to gui
    m_menuLayout->add(m_playButton);
    m_menuLayout->add(m_quitButton);
    m_menuLayout->insertSpace(1, 0.5f);

    m_group->add(m_menuLayout);
  }

  // Button callbacks
  void MainMenuScreenComponent::PlayButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

  void MainMenuScreenComponent::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }

}