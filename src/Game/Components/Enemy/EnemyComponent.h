#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <Engine/Managers/EventManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Core/EventData.h"

namespace Game
{

  enum class EnemyAIStates
  {
    CHASING,
    STUNNED,
    TEST,
  };

  class EnemyComponent : public Engine::IComponent
  {
  public:
    EnemyComponent(Engine::GameObject& obj);
    ~EnemyComponent() override = default;

    void OnDestroy() override;

  private:
    Engine::GameObject* m_target = nullptr;
    Engine::PushdownStateMachine<Engine::IState<EnemyAIStates>> m_stateMachine;
  };
}