#pragma once
#include "../EnemyComponent.h"

namespace Game
{
  
  class TestEnemyState : public Engine::IState<EnemyAIStates>
  {
  public:
    TestEnemyState(Engine::GameObject& owner, Engine::IState<EnemyAIStates>::StateMachine& sm)
      : IState(owner, sm, EnemyAIStates::TEST) {}

    ~TestEnemyState() override = default;

    void Update(float dt) override { LOG_WARN("TEST STATE"); };
  };

}