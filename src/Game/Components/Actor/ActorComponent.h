#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Debug/IDebuggable.h>

#include "Commands.h"
#include "RPGComponent.h"
#include <queue>
#include <memory>
#include <tuple>

#include <Engine/Core/Events.h>
#include <Engine/Core/Signal.h>

#include "../../Core/EventData.h"
namespace Game
{

  enum Actor_DamageType
  {
    Bullet,
    Collision,
    DOT, // e.g. burning, should apply a knockback
  };

  struct DamageTakenData
  {
    float Amount;
    Engine::GameObject* Source;
    Actor_DamageType Type;
  };

	class ActorComponent : public Engine::IComponent, public Engine::IDebuggableComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
  {
  public:
    // Amount, source, type

    ActorComponent(Engine::GameObject& obj);
    ~ActorComponent() override;

    void VirtualOnCreate() override;
    void Update(float dt) override;

    template<typename T,
      typename ... Args,
      typename = std::enable_if_t< std::is_base_of<ICommand, T>::value >
    >
      void AddCommand(Args&& ... args);

    void Move(Engine::math::Vec2 dir);
    void KnockBack(Engine::math::Vec2 dir);
    void Rotate(float angle);
    void ApplyDamage(float amount, Engine::GameObject* source, Actor_DamageType type);

    void Debug(Engine::view::IViewStrategy* viewStrategy) override;
   
    Engine::math::Vec2 GetMovingDir() { return m_movingDir; };
    // Bool references for animation transitions
		const bool& IsMoving() { return m_isMoving; };

		Engine::Signal<void>            OnZeroHealth;
		Engine::Signal<DamageTakenData> OnDamageTaken;
	protected:
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

  private:
    bool m_isMoving = false;
    Engine::math::Vec2 m_movingDir = { 0.0f, 0.0f };
    RPGComponent* m_RPGComponent;
    Engine::SpriteDrawableComponent* m_spriteComponent;
    std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    bool isFlipped = false;
  };
};

#include "ActorComponent.inl"