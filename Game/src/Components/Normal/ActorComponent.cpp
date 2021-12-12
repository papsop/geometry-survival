#include "ActorComponent.h"

#include "../../GameObject.h"
#include "../../Utils/Vec2f.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include<math.h>

namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) 
        : IComponent(obj)
    {
    }

    void ActorComponent::OnGameObjectChanged()
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
            tmpRigidbody->RotateToAngle(angle * 180 / M_PI + 90);
        }
    }

    void ActorComponent::Update(float dt)
    {
    }
};