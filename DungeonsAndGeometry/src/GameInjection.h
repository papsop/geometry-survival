#pragma once
#include "Core/ApplicationInjection.h"
#include "Application.h"
#include "Core/GameObject.h"

#include "Components/Player/InputComponent.h"
#include "Components/Actor/ActorComponent.h"
namespace Game
{
    class Engine::Application;
    class GameInjection : public Engine::ApplicationInjection
    {
    public:
        void RegisterGameComponents(Engine::Application& app) override
        {
            // Order is important
            app.GetSubsystemManager().RegisterComponentType<InputComponent>();
            app.GetSubsystemManager().RegisterComponentType<ActorComponent>();
            //app.GetSubsystemManager().RegisterComponentSubsystem<Engine::InputComponent>(new Engine::ComponentSubsystem());
            //app.GetSubsystemManager().RegisterComponentSubsystem<Engine::ActorComponent>(new Engine::ComponentSubsystem());
        }

        void BeforeGameLoop(Engine::Application& app) override
        {
            auto obj = Engine::EntityManager::Get().CreateEntityReturnEntity("Player");
            uint32_t objID = 0;
            if (auto tmp = obj.lock())
            {
                objID = tmp->ID;
                tmp->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
                tmp->AddComponent<Engine::RigidbodyComponent>(*tmp);
                tmp->AddComponent<Engine::TriangleComponent>(*tmp, sf::Color::Blue, 0);
                tmp->AddComponent<InputComponent>(*tmp);
                tmp->AddComponent<ActorComponent>(*tmp);
            }
        }
    };
}


