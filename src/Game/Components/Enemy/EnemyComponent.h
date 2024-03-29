#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/EventManager.h>

#include "../../Core/EventData.h"

namespace Game {

enum class EnemyAIStates {
  CHASING,
  STUNNED,
  TEST,
};

struct EnemyComponentDef {
  float DamagePerSecond;
};

class EnemyComponent : public Engine::IComponent,
                       public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>,
                       public Engine::IEventListener<event::E_GameStateChanged> {
 public:
  EnemyComponent(Engine::GameObject& obj, EnemyComponentDef def);
  ~EnemyComponent() override = default;

  void VirtualOnCreate() override;
  void OnDestroy() override;
  Engine::GameObject* GetTarget() const { return m_target; }

  void Update(float dt) override;
  void OnZeroHealthCallback();

  void OnCollisionStart(Engine::CollisionData& collision) override;
  void OnCollisionEnd(Engine::CollisionData& collision) override;

  const bool& IsDying() { return m_isDying; }
  void OnDeathAnimationFinishedCallback();

 protected:
  void VirtualOnActivated() override;
  void VirtualOnDeactivated() override;

  void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;
  void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

 private:
  Engine::GameObject* m_target = nullptr;
  Engine::PushdownStateMachine<Engine::IState<EnemyAIStates>> m_stateMachine;
  Engine::SpriteDrawableComponent* m_spriteDrawableComponent = nullptr;
  bool m_isTouchingTarget = false;
  bool m_isDying = false;
  float m_damagePerSecond;

  void OnDeathImpl();
};
}  // namespace Game
