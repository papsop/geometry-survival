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
    // Main layout
    m_settingsLayout = tgui::VerticalLayout::create();
    m_settingsLayout->setOrigin(0.5f, 0.0f);
    m_settingsLayout->setSize("50%", "60%");
    m_settingsLayout->setPosition("50%", "20%");

    // Header
		m_headerLabel = tgui::Label::create("SETTINGS");
    m_headerLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    m_headerLabel->setTextSize(48);


    // Resolution
    m_resolutionLayout = tgui::HorizontalLayout::create();

		m_resolutionLabel = tgui::Label::create("Resolution:");
    m_resolutionLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    m_resolutionLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    m_resolutionLabel->setTextSize(32);

    m_resolutionComboBox = tgui::ComboBox::create();
    m_resolutionComboBox->addItem("test");
    m_resolutionComboBox->addItem("test2");
    m_resolutionComboBox->addItem("test3");

    m_resolutionLayout->add(m_resolutionLabel);
    m_resolutionLayout->add(m_resolutionComboBox);

    // Buttons
		m_buttonsLayout = tgui::HorizontalLayout::create();
    
    m_saveSettingsButton  = tgui::Button::create("Save");
    m_backToMenuButton    = tgui::Button::create("Back");
    
    m_saveSettingsButton->onClick(&SettingsScreenComponent::SaveSettingsCallback, this);
    m_backToMenuButton->onClick(&SettingsScreenComponent::BackToMenuCallback, this);

    m_buttonsLayout->add(m_saveSettingsButton);
    m_buttonsLayout->add(m_backToMenuButton);


    // =======================

    // Settings Layout
    m_settingsLayout->add(m_headerLabel);
    m_settingsLayout->addSpace(0.5f);
    m_settingsLayout->add(m_resolutionLayout);
    m_settingsLayout->addSpace(0.5f);
    m_settingsLayout->add(m_buttonsLayout);

    // Screen group
    m_group->add(m_settingsLayout);
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
	void SettingsScreenComponent::SaveSettingsCallback()
	{

	}

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