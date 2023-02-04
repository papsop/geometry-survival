#include "SettingsScreenComponent.h"
#include <Engine/Application.h>
#include "../../Managers/GameManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include "Controllers/MainMenuUIControllerComponent.h"
namespace Game
{

  SettingsScreenComponent::SettingsScreenComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {}


  void SettingsScreenComponent::RegisterUIElements()
  {
    // Layout
    m_menuLayout = tgui::VerticalLayout::create();
    m_menuLayout->setSize("30%", "45d%");
    m_menuLayout->setOrigin(0.5f, 0.0f);
    m_menuLayout->setPosition("50%", "20%");

    // menu label
    m_menuLabel = tgui::Label::create("Settings");
    m_menuLayout->setOrigin(0.5f, 0.0f);
    m_menuLabel->setTextSize(72);

    // back to menu button
    m_backToMenuButton = tgui::Button::create("Back to menu");

    // callbacks
    m_backToMenuButton->onClick(&SettingsScreenComponent::BackToMenuCallback, this);

    // add to gui
    m_menuLayout->add(m_menuLabel);
    m_menuLayout->add(m_backToMenuButton);

    m_group->add(m_menuLayout);
  }

  void SettingsScreenComponent::UIShown()
  {
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
  }

  void SettingsScreenComponent::UIHidden()
  {
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
  }

  void SettingsScreenComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    BackToMenuCallback();
  }

  // Callbacks
  void SettingsScreenComponent::BackToMenuCallback()
  {
    auto* ingameController = Owner.GetComponent<IngameUIControllerComponent>();
    if (ingameController)
    {
      ingameController->SetState(IngameUIControllerComponent::IngameUIState::MENU);
      return;
    }

		auto* mainMenuController = Owner.GetComponent<MainMenuUIControllerComponent>();
		if (mainMenuController)
		{
      mainMenuController->SetState(MainMenuUIControllerComponent::MainMenuUIStates::MENU);
      return;
		}

  }

}