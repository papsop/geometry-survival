#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <Engine/Managers/EventManager.h>
#include <Engine/Core/Events.h>
#include "../../Core/EventData.h"

namespace Game
{
  class EnemyComponent : public Engine::IComponent, public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>
  {
  public:
    EnemyComponent(Engine::GameObject& obj);
    ~EnemyComponent() override = default;

    void OnDestroy() override;
    Engine::GameObject* GetTarget();

  protected:
    void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    Engine::GameObject* m_target = nullptr;
  };
}