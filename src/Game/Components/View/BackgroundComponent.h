#pragma once
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"

namespace Game
{
  class BackgroundComponent : public Engine::IComponent
  {
  public:
    BackgroundComponent(Engine::GameObject& obj, Engine::GameObject* target);
    ~BackgroundComponent() override;

    void OnCreate() override;
    void FixedUpdate(float dt) override;
  protected:

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    Engine::GameObject* m_target;

  };
}