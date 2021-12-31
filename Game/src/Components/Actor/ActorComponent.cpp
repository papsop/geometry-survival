#include "ActorComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) 
        : IComponent(obj)
        , m_commandsQueue()
    {
        ACTORSUBSYSTEM_REGISTER(this);
    }

    ActorComponent::~ActorComponent()
    {
        ACTORSUBSYSTEM_UNREGISTER(this);
    }

    void ActorComponent::OnGameObjectChanged()
    {
        m_rigidbodyComponent = Owner.GetComponent<RigidbodyComponent>();
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

    void ActorComponent::Rotate(float angle)
    {
        //LOG_INFO("ActorComponent::Rotate(%d)", angle);
        Owner.GetTransform().Rotation = angle;
        //if (auto tmp = m_rigidbodyComponent.lock())
        //    tmp->Rotation = angle;
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