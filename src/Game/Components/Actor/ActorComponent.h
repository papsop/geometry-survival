#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>
#include "Commands.h"
#include "RPGComponent.h"
#include <queue>
#include <memory>

namespace Game
{
    class ActorComponent : public Engine::IComponent, public Engine::IDebuggableComponent
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
        void ApplyDamage(float amount);
        void WeaponFire();
        void WeaponReload();

        void ProcessMessage(const Engine::Message& message) override;

        void Debug(Engine::view::IViewStrategy* viewStrategy) override;

    private:
        RPGComponent* m_RPGComponent;
        std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    };
};

#include "ActorComponent.inl"