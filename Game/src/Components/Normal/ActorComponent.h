#pragma once
#include "../IComponent.h"
#include "RigidbodyComponent.h"
#include <memory>

namespace Game
{
    class ActorComponent : public IComponent
    {
    public:
        ActorComponent(GameObject& obj);
        ~ActorComponent() override = default;

        void Init() override;
        void Update(float dt) override;
        void SetMovementVector(sf::Vector2f movement);
        void RotateTo(sf::Vector2f target);
    private:
        float m_movementSpeed = 200.0f;
        std::weak_ptr<RigidbodyComponent> m_rigidbodyComponent;
    };
};


