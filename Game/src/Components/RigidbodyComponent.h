#pragma once
#include "IComponent.h"
#include "Transform.h"

namespace Game
{
    class RigidbodyComponent : public IComponent
    {
    public:
        RigidbodyComponent(GameObject& obj);

        void Update(float dt) override;
        void OnGameObjectChanged() override;

        //void RotateToAngle(float targetAngle);
        //void Move(sf::Vector2f moveDirection);
        sf::Vector2f Velocity = sf::Vector2f(0.0f, 0.0f);

    private:
        Transform& m_ownerTransform;

        float m_maxRotationSpeed = 270.0f;

        float m_targetRotationAngle = 0.0f;
        float m_rotationLerpT = 0.0f;
        float m_timeToRotate = 0.0f;
    };
}


