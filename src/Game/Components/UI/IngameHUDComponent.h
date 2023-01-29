#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/EventData.h"
#include "../../Core/StateMachines/UIStateMachine.h"

#include "../Player/LevelComponent.h"
#include "../Actor/WeaponComponent.h"
#include "../Actor/RPGComponent.h"

#include "../../Managers/GameManager.h"

namespace Game
{
  class IngameHUDComponent : public Engine::IUIComponent
    , public Engine::IEventListener<Engine::event::E_EscapeAction>
    , public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>
    , public Engine::IEventListener<event::E_PlayerLeveledUp>
    , public Engine::IEventListener<event::E_PlayerDied>
  {
  public:
    IngameHUDComponent(Engine::GameObject& obj);
    ~IngameHUDComponent() override = default;

    void Update(float dt) override;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;
    void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;
    void ReceiveEvent(const event::E_PlayerLeveledUp& eventData) override;
    void ReceiveEvent(const event::E_PlayerDied& eventData) override;

    void RegisterUIElements() override;

    void UIShown() override;
    void UIHidden() override;

  private:
    void ResetPlayerComponents(Engine::GameObject* player);
    // Player components
    LevelComponent* m_levelComponent = nullptr;
    WeaponComponent* m_weaponComponent = nullptr;
    RPGComponent* m_rpgComponent = nullptr;

    // UI Members
    tgui::Label::Ptr m_levelLabel;
    tgui::Panel::Ptr m_experienceBar;
    tgui::Label::Ptr m_ammoLabel;
    tgui::Label::Ptr m_timerLabel;
    tgui::Label::Ptr m_healthLabel;

    // Timer
    GameTimer& m_gameTimer;
  };
}