#pragma once
#include <Engine/Core/Scene/IScene.h>

namespace Game
{
  class GameMenuScene : public Engine::IScene
  {
  public:
    void InstantiateObjects() const override;
  };
}