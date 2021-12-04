#include "ActorComponent.h"

#include "../../GameObject.h"

namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) : IComponent(obj)
    {
    }

    void ActorComponent::Init()
    {
        m_transformComponent = m_owner.GetComponent<TransformComponent>();
    }

    void ActorComponent::SetMovementVector(sf::Vector2f movement)
    {
        if (auto tmp = m_transformComponent.lock())
        {
            tmp->SetVelocity(movement * m_movementSpeed);
        }
    }

    void ActorComponent::Update(float dt)
    {
    }
};