#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include <Engine/Managers/PhysicsManager.h>

namespace Game
{
  class EnemyComponent : public Engine::IComponent
  {
  public:
    EnemyComponent(Engine::GameObject& obj, Engine::GameObject* target);
    ~EnemyComponent() override;

  private:
  };
}