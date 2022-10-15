#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class GameHUDComponent : public Engine::IComponent
  {
  public:
    GameHUDComponent(Engine::GameObject& obj);
    ~GameHUDComponent() override = default;

    void OnCreate() override;
    void OnDestroy() override;

  protected:
    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;
  };
}