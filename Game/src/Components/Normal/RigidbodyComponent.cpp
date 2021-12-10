#include "RigidbodyComponent.h"
#include "../../GameObject.h"
#include <cmath>
#include <iostream>

namespace Game
{
    RigidbodyComponent::RigidbodyComponent(GameObject& obj)
        : IUpdatableComponent(obj)
        , m_ownerTransform(m_owner.GetTransform())
        , m_targetRotationAngle(m_ownerTransform.Rotation)
    {

    }

    void RigidbodyComponent::Init() {}

    void RigidbodyComponent::RotateToAngle(float targetAngle)
    {
        if (m_ownerTransform.Rotation != targetAngle)
        {
            m_timeToRotate = abs(m_ownerTransform.Rotation - m_targetRotationAngle) / m_maxRotationSpeed;
            m_rotationLerpT = 0.0f;
            m_targetRotationAngle = targetAngle;
        }
    }

    void RigidbodyComponent::Move(sf::Vector2f moveDirection)
    {
        m_velocity = moveDirection * m_maxMovementSpeed;
    }

    void RigidbodyComponent::Update(float dt)
    {
        //Movement
        m_ownerTransform.Position += m_velocity * dt;

        // Rotation
        if (m_timeToRotate > 0.0f)
        {
            m_rotationLerpT += dt / m_timeToRotate;
            m_rotationLerpT = fmin(1.0f, m_rotationLerpT);
            if (m_ownerTransform.Rotation != m_targetRotationAngle)
            {
                float lerp = m_ownerTransform.Rotation * (1.0f - m_rotationLerpT) + m_targetRotationAngle * m_rotationLerpT;
                m_ownerTransform.Rotation = lerp;
            }
            else
                m_timeToRotate = 0.0f;
        }
    }
};