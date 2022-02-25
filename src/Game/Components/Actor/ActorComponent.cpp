#include "ActorComponent.h"
#include "WeaponComponent.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>

namespace Game
{

    ActorComponent::ActorComponent(Engine::GameObject& obj)
        : IComponent(obj)
        , m_commandsQueue()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);

        Requires<Engine::RigidbodyComponent>();
    }

    ActorComponent::~ActorComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void ActorComponent::AddCommand(std::unique_ptr<ICommand> command)
    {
        m_commandsQueue.push(std::move(command));
    }
     
    void ActorComponent::Move(Engine::math::Vec2 dir)
    {
        auto rb = Owner.GetComponent<Engine::RigidbodyComponent>();
        if(rb != nullptr)
            rb->Velocity = dir * m_movementSpeed;
    }

    void ActorComponent::Rotate(float angle)
    {
        Owner.GetTransform().Rotation = angle;
    }

    void ActorComponent::Fire()
    {
        auto weaponComp = Owner.GetComponent<WeaponComponent>();
        if (weaponComp) 
        {
            weaponComp->Fire();
        }
    }

    void ActorComponent::Update(float dt)
    {
        while (!m_commandsQueue.empty())
        {
            m_commandsQueue.front()->Execute(*this);
            m_commandsQueue.pop();
        }
    }
};