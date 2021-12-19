#pragma once
#include "IComponent.h"
#include "RigidbodyComponent.h"
#include "Commands.h"
#include <memory>

namespace Game
{
    class ActorComponent : public IComponent
    {
    public:
        ActorComponent(GameObject& obj);
        ~ActorComponent() override = default;

        void OnGameObjectChanged() override;
        void Update(float dt) override;
        
        void AddCommand(ICommand& command);
        
        void Move(float dX, float dY);

    private:
        float m_movementSpeed = 500.0f;
        std::weak_ptr<RigidbodyComponent> m_rigidbodyComponent;
    };
};


