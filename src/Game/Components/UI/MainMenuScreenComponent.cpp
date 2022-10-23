#include "MainMenuScreenComponent.h"
#include <Engine/Application.h>
#include "../../Managers/GameManager.h"
#include <TGUI/Animation.hpp>
namespace Game
{

  MainMenuScreenComponent::MainMenuScreenComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {

  }

  void MainMenuScreenComponent::OnCreate()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (!gui) return;

    // Layout
    m_menuLayout = tgui::VerticalLayout::create();
    m_menuLayout->setSize("30%", "45d%");
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

    m_playButton->setVisible(false);
    m_quitButton->setVisible(false);
    m_menuLayout->setVisible(false);

    gui->add(m_menuLayout);
  }

  void MainMenuScreenComponent::OnDestroy()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (!gui) return;

    gui->remove(m_playButton);
    gui->remove(m_quitButton);
    gui->remove(m_menuLayout);
  }

  void MainMenuScreenComponent::VirtualOnActivated()
  {
    m_playButton->setVisible(true);
    m_quitButton->setVisible(true);
    m_menuLayout->setVisible(true);
  }

  void MainMenuScreenComponent::VirtualOnDeactivated()
  {
    m_playButton->setVisible(false);
    m_quitButton->setVisible(false);
    m_menuLayout->setVisible(false);
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