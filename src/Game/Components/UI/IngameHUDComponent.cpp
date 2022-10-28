#include "IngameHUDComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"

#include "IngameUIControllerComponent.h"

namespace Game
{

  IngameHUDComponent::IngameHUDComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {
  }

  void IngameHUDComponent::RegisterUIElements()
  {
    
    m_levelLabel = tgui::Label::create("0");
    m_levelLabel->setOrigin(0.5f, 0.5f);
    m_levelLabel->setPosition("50%", "10%");
    m_levelLabel->setTextSize(48);
    m_group->add(m_levelLabel);

    m_experienceBar = tgui::Panel::create();
    m_experienceBar->setOrigin(0.0f, 0.0f);
    m_experienceBar->setPosition(0, 0);
    m_experienceBar->setSize("100%", "20");
    m_group->add(m_experienceBar);

    m_ammoLabel = tgui::Label::create("0/0");
    m_ammoLabel->setOrigin(1.0f, 1.0f);
    m_ammoLabel->setPosition("100%", "100%");
    m_ammoLabel->setTextSize(48);
    m_group->add(m_ammoLabel);
  }

  void IngameHUDComponent::UIShown()
  {
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
    IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
    
  }

  void IngameHUDComponent::UIHidden()
  {
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
    IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
  }

  void IngameHUDComponent::Update(float dt)
  {
    if (m_levelComponent)
    {
      m_levelLabel->setText(tgui::String(m_levelComponent->GetCurrentLevel()));

      tgui::String levelProgress = tgui::String(m_levelComponent->GetCurrentLevelProgress()*100) + "%";
      m_experienceBar->setSize(levelProgress,m_experienceBar->getSize().y);
    }

    if (m_weaponComponent)
    {
      tgui::String ammoString = tgui::String(m_weaponComponent->GetCurrentAmmo()) + "/" + tgui::String(m_weaponComponent->GetMaxAmmo());
      m_ammoLabel->setText(ammoString);
    }
  }

  void IngameHUDComponent::ResetPlayerComponents(Engine::GameObject* player)
  {
    if (player)
    {
      m_levelComponent = player->GetComponent<LevelComponent>();
      m_weaponComponent = player->GetComponent<WeaponComponent>();
    }
    else
    {
      m_levelComponent = nullptr;
      m_weaponComponent = nullptr;
    }
  }

  void IngameHUDComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::MENU);
    }
  }

  void IngameHUDComponent::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData)
  {
    ResetPlayerComponents(eventData.PlayerObject);
  }

}