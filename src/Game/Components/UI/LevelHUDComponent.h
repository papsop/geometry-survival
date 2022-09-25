#pragma once
#include "../Player/LevelComponent.h"

#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{

  class LevelHUDComponent : public Engine::IComponent
  {
  public:
    LevelHUDComponent(Engine::GameObject& obj);
    ~LevelHUDComponent() override;


    void OnCreate() override;
    void Update(float dt) override;
  private:
    LevelComponent* m_playerLevelComponent = nullptr;
  };

}