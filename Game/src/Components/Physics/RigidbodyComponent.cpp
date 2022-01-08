#include "RigidbodyComponent.h"
#include "../../Core/GameObject.h"
#include "../../Application.h"
#include <cmath>
#include <iostream>

namespace Game
{
    RigidbodyComponent::RigidbodyComponent(GameObject& obj)
        : IComponent(obj)
        , IDebugDrawComponent()
        , m_ownerTransform(obj.GetTransform())
        , m_targetRotationAngle(obj.GetTransform().Rotation)
    {
        PHYSICSSUBSYSTEM_REGISTER(this);
    }

    RigidbodyComponent::~RigidbodyComponent()
    {
        PHYSICSSUBSYSTEM_UNREGISTER(this);
    }

    void RigidbodyComponent::OnGameObjectChanged() {}

    //void RigidbodyComponent::RotateToAngle(float targetAngle)
    //{
    //    if (m_ownerTransform.Rotation != targetAngle)
    //    {
    //        m_timeToRotate = abs(m_ownerTransform.Rotation - m_targetRotationAngle) / m_maxRotationSpeed;
    //        m_rotationLerpT = 0.0f;
    //        m_targetRotationAngle = targetAngle;
    //    }
    //}

    void RigidbodyComponent::Update(float dt)
    {
        //Movement
        m_ownerTransform.Position += Velocity * dt;
        // Rotation
        //if (m_timeToRotate > 0.0f)
        //{
        //    m_rotationLerpT += dt / m_timeToRotate;
        //    m_rotationLerpT = fmin(1.0f, m_rotationLerpT);
        //    if (m_ownerTransform.Rotation != m_targetRotationAngle)
        //    {
        //        float lerp = m_ownerTransform.Rotation * (1.0f - m_rotationLerpT) + m_targetRotationAngle * m_rotationLerpT;
        //        m_ownerTransform.Rotation = lerp;
        //    }
        //    else
        //        m_timeToRotate = 0.0f;
        //}
    }

    void RigidbodyComponent::DebugDraw(view::IViewStrategy* viewStrategy)
    {
        // draw forward vector
        sf::Vector2f secondPos = m_ownerTransform.Position + m_ownerTransform.Forward() * 50.0f;
        view::Line line;
        line.Points[0] = sf::Vertex(m_ownerTransform.Position);
        line.Points[1] = sf::Vertex(secondPos);

        viewStrategy->Render(line);
    }
};