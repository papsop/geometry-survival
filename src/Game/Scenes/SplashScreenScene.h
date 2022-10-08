#pragma once
#include <Engine/Core/Scene/IScene.h>

namespace Game
{
  class SplashScreenScene : public Engine::IScene
  {
  public:
    SplashScreenScene() = default;
    ~SplashScreenScene() = default;

    void InstantiateObjects() const override;
  };
}