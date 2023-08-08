#pragma once
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/Events.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>

#include "../../Core/EventData.h"

namespace Game
{
  class BackgroundComponent : public Engine::IComponent
  {
  public:
    BackgroundComponent(Engine::GameObject& obj);
    ~BackgroundComponent() override;

    void VirtualOnCreate() override;
    void FixedUpdate(float dt) override;

    void RenderManagerSettingsChanged();

    void OnDestroy() override;

  protected:

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    Engine::SpriteDrawableComponent* m_spriteComponent;

  };
}