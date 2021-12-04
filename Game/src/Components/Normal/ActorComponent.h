#pragma once
#include "../IComponent.h"
#include "../Normal/TransformComponent.h"
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
        void SetMovementVector(sf::Vector2f);
    private:
        std::weak_ptr<TransformComponent> m_transformComponent;
        float m_movementSpeed = 200.0f;
    };
};


