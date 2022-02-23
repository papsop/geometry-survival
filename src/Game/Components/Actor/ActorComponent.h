#pragma once
#include <Engine/Components/Core.h>
#include "Commands.h"
#include <queue>
#include <memory>

namespace Game
{
    class ActorComponent : public Engine::IComponent
    {
    public:
        ActorComponent(Engine::GameObject& obj);
        ~ActorComponent() override;

        void OnGameObjectChanged() override;
        void Update(float dt) override;
        
        void AddCommand(std::unique_ptr<ICommand> command);
        
        void Move(sf::Vector2f dir);
        void Rotate(float angle);
        void Fire();

    private:
        float m_movementSpeed = 500.0f;
        std::queue<std::unique_ptr<ICommand>> m_commandsQueue;
    };
};


