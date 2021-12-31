#pragma once
#include "../Core.h"
#include "../Physics.h"
#include <queue>
#include <memory>

namespace Game
{
    class ActorComponent : public IComponent
    {
    public:
        ActorComponent(GameObject& obj);
        ~ActorComponent() override;

        void OnGameObjectChanged() override;
        void Update(float dt) override;
        
        void AddCommand(std::unique_ptr<ICommand> command);
        
        void Move(float dX, float dY);
        void Rotate(float angle);

    private:
        float m_movementSpeed = 500.0f;
        std::weak_ptr<RigidbodyComponent> m_rigidbodyComponent;
        std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    };
};


