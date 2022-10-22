#pragma once
#include <Engine/Core/Scene/IScene.h>

namespace Game
{
  class SettingsScreenScene : public Engine::IScene
  {
  public:
    void InstantiateObjects() const override;
  };
}