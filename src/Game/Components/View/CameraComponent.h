#pragma once
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/ViewManager.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"
namespace Game
{
  class CameraComponent : public Engine::IComponent, public Engine::IDebuggableComponent,
		public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>,
		public Engine::IEventListener<event::E_GameStateChanged>
  {
  public:
    CameraComponent(Engine::GameObject& obj, Engine::GameObject* target);
    ~CameraComponent() override;
    void OnCreate() override;
    void Update(float dt) override;

    void SetTarget(Engine::GameObject* newTarget);

    void Debug(Engine::view::IViewStrategy* viewStrategy) override;

  protected:
    void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;
    void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    Engine::CameraData m_cameraData;
    Engine::GameObject* m_target;


	};
}