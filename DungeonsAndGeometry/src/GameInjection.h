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
        }

        void BeforeGameLoop(Engine::Application& app) override
        {

            auto& scene = Engine::SceneManager::Get().CreateScene();

            auto player = Engine::EntityManager::Get().CreateEntity("Player");
            player->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
            player->AddComponent<Engine::RigidbodyComponent>();
            player->AddComponent<Engine::TriangleComponent>(sf::Color::Blue, 0);
            player->AddComponent<InputComponent>();
            player->AddComponent<ActorComponent>();

            auto enemy = Engine::EntityManager::Get().CreateEntity("Enemy");

            scene.AddGameObject(player);
            scene.AddGameObject(enemy);


            Engine::SceneManager::Get().SetActiveScene(scene.ID);
        }
    };
}


