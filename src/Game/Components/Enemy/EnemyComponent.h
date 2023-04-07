#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/ComponentManager.h>
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

  class EnemyComponent : public Engine::IComponent,
    public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>
  {
  public:
    EnemyComponent(Engine::GameObject& obj);
    ~EnemyComponent() override = default;

    void OnCreate() override;
    void OnDestroy() override;
    Engine::GameObject* GetTarget() const { return m_target; }


    void Update(float dt) override;
    void OnDeath();

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

    void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;

  private:
    Engine::GameObject* m_target = nullptr;
    Engine::PushdownStateMachine<Engine::IState<EnemyAIStates>> m_stateMachine;


  };
}