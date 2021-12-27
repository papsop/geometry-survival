#include "ActorComponent.h"

#include "../../Core/GameObject.h"
#include <iostream>

namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) 
        : IComponent(obj)
        , m_commandsQueue()
    {
    }

    void ActorComponent::OnGameObjectChanged()
    {
        m_rigidbodyComponent = m_owner.GetComponent<RigidbodyComponent>();
    }

    void ActorComponent::AddCommand(std::unique_ptr<ICommand> command)
    {
        m_commandsQueue.push(std::move(command));
    }
     
    void ActorComponent::Move(float dX, float dY)
    {
        if (auto tmp = m_rigidbodyComponent.lock())
            tmp->Velocity = sf::Vector2f(dX, dY) * m_movementSpeed;
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