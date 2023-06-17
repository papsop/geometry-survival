#pragma once

#include <Engine/Components/Core.h>
#include <Engine/Managers/InputManager.h>

#include <Engine/Core/Events.h>
#include "../../Core/EventData.h"
#include "../Actor/ActorComponent.h"
#include "../Actor/WeaponComponent.h"

namespace Game
{
  class InputComponent : public Engine::IComponent,
    public Engine::IEventListener<event::E_GameStateChanged>
  {
  public:
    InputComponent(Engine::GameObject& obj);
    ~InputComponent() override;

    void VirtualOnCreate() override;
    void Update(float dt) override;

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

  private:
    Engine::InputManager& m_inputManager;
    ActorComponent* m_actorComponent;
    WeaponComponent* m_weaponComponent;

    float m_previousUpdateHorizontal = 0.0f;
    float m_previousUpdateVertical = 0.0f;

    float m_previousUpdateRotation = 0.0f;
  };
};


