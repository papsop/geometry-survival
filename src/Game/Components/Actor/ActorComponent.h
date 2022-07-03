#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>
#include "Commands.h"
#include "../../RPG/RPGActor.h"
#include <queue>
#include <memory>

namespace Game
{
    class ActorComponent : public Engine::IComponent, public Engine::IDebuggableComponent
    {
    public:
        ActorComponent(Engine::GameObject& obj, float movementSpeed);
        ~ActorComponent() override;

        RPGActor* GetRPGActor() { return m_RPGActor.get(); };

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
        void Fire();

        void ProcessMessage(const Engine::Message& message) override;


        void OnCollisionStart(Engine::GameObject* other) override;


        void Debug(Engine::view::IViewStrategy* viewStrategy) override;

    private:
        std::unique_ptr<RPGActor> m_RPGActor;
        float m_movementSpeed = 5.0f;
        std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    };
};

#include "ActorComponent.inl"