#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
  class EnemyComponent : public Engine::IComponent
  {
  public:
    EnemyComponent(Engine::GameObject& obj);
    ~EnemyComponent() override = default;

    void OnDestroy() override;

  private:
  };
}