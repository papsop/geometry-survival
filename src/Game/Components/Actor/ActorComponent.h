#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Debug/IDebuggable.h>

#include "Commands.h"
#include "RPGComponent.h"
#include <queue>
#include <memory>

#include <Engine/Core/Events.h>
#include <Engine/Core/Signal.h>

#include "../../Core/EventData.h"
namespace Game
{

  enum Actor_DamageSource
  {
    Bullet,
    Collision,
    DOT, // e.g. burning, should apply a knockback
  };

	class ActorComponent : public Engine::IComponent, public Engine::IDebuggableComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
  {
  public:
    ActorComponent(Engine::GameObject& obj);
    ~ActorComponent() override;

    void OnCreate() override;
    void Update(float dt) override;

    template<typename T,
      typename ... Args,
      typename = std::enable_if_t< std::is_base_of<ICommand, T>::value >
    >
      void AddCommand(Args&& ... args);

    void Move(Engine::math::Vec2 dir);
    void KnockBack(Engine::math::Vec2 dir);
    void Rotate(float angle);
    void ApplyDamage(float amount, Actor_DamageSource source);

    void Debug(Engine::view::IViewStrategy* viewStrategy) override;
    
    Engine::Signal OnZeroHealth;
	protected:
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
  private:
    RPGComponent* m_RPGComponent;
    Engine::SpriteDrawableComponent* m_spriteComponent;
    std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    bool isFlipped = false;
  };
};

#include "ActorComponent.inl"