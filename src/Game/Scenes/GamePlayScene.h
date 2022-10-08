#pragma once
#include <Engine/Core/Scene/IScene.h>

namespace Game
{
  class GamePlayScene : public Engine::IScene
  {
  public:
    GamePlayScene() = default;
    ~GamePlayScene() = default;

    void InstantiateObjects() const override;
  };
}