#pragma once

#include <Engine/Components/Core.h>
#include <Engine/Managers/InputManager.h>

namespace Game
{
  class PlayerSpawnerComponent : public Engine::IComponent
  {
  public:
    PlayerSpawnerComponent(Engine::GameObject& obj);
    ~PlayerSpawnerComponent() override = default;

    void CreatePlayerObject();

  private:
    

  };
};
