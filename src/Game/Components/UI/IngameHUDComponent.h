#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/EventData.h"

#include "../Player/LevelComponent.h"
#include "../Actor/RPGComponent.h"

#include "../../Managers/GameManager.h"

namespace Game
{
  class IngameHUDComponent : public Engine::IImGuiComponent
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

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    void ResetPlayerComponents(Engine::GameObject* player);
    // Player components
    LevelComponent* m_levelComponent = nullptr;
    //WeaponComponent* m_weaponComponent = nullptr;
    RPGComponent* m_rpgComponent = nullptr;

    // Timer
    GameTimer& m_gameTimer;
  };
}