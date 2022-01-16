#include "ActorComponent.h"

#include "Core/GameObject.h"
#include "Application.h"

namespace Game
{

    ActorComponent::ActorComponent(Engine::GameObject &obj)
        : IComponent(obj)
        , m_commandsQueue()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    ActorComponent::~ActorComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void ActorComponent::OnGameObjectChanged(){}

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
        if (m_currentShootingCooldown <= 0.0f)
        {
            LOG_WARN("Firing");
            m_currentShootingCooldown = m_defaultShootingCooldown;
        }
    }

    void ActorComponent::Update(float dt)
    {
        while (!m_commandsQueue.empty())
        {
            m_commandsQueue.front()->Execute(*this);
            m_commandsQueue.pop();
        }

        m_currentShootingCooldown -= dt;
    }
};