#pragma once
#include <Engine/Core/Scene/IScene.h>

namespace Game
{
  class MainMenuScene : public Engine::IScene
  {
  public:
    MainMenuScene() = default;
    ~MainMenuScene() = default;

    void InstantiateScene() const override;
  };
}