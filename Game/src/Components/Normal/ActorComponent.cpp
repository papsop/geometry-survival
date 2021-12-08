#include "ActorComponent.h"

#include "../../GameObject.h"
#include "../../Utils/Vec2f.h"
#include <iostream>
namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) : IUpdatableComponent(obj)
    {
    }

    void ActorComponent::Init()
    {
        m_rigidbodyComponent = m_owner.GetComponent<RigidbodyComponent>();
    }

    void ActorComponent::SetMovementVector(sf::Vector2f movement)
    {
        if (auto tmpRigidbody = m_rigidbodyComponent.lock())
        {
            tmpRigidbody->Move(movement);
        }
    }

    void ActorComponent::RotateTo(sf::Vector2f target)
    {
        if (auto tmpRigidbody = m_rigidbodyComponent.lock())
        {
            Transform& transform = m_owner.GetTransform();
            auto dirToMouse = target - transform.Position;
            float angle = atan2(dirToMouse.y, dirToMouse.x);
            tmpRigidbody->RotateToAngle(angle * 180.0f / 3.14259f);
        }
    }

    void ActorComponent::Update(float dt)
    {
    }
};