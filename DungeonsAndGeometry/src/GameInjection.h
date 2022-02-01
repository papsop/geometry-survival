#pragma once
#include "Core/ApplicationInjection.h"
#include "Application.h"
#include "Core/GameObject.h"

#include "Components/Player/InputComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/SplashScreen/SplashBackground.h"
#include "Components/SplashScreen/SplashTitle.h"
#include "Components/SplashScreen/SplashController.h"
#include "Components/SplashScreen/SplashShape.h"

#include "Debug/Backend/WindowBackendStrategy.h"
namespace Game
{
    class Engine::Application;
    class GameInjection : public Engine::ApplicationInjection
    {
    public:
        void RegisterGameComponents(Engine::Application& app) override
        {
            // Order is important
            Engine::SubsystemManager::Get().RegisterComponentType<SplashShape>();
            Engine::SubsystemManager::Get().RegisterComponentType<SplashController>();
            Engine::SubsystemManager::Get().RegisterComponentType<InputComponent>();
            Engine::SubsystemManager::Get().RegisterComponentType<ActorComponent>();
        }

        void BeforeGameLoop(Engine::Application& app) override
        {
            // setup logger
            Engine::Logger::Instance().SetBackend(std::make_unique<Engine::WindowBackendStrategy>());
            Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::INFO);

            // Scene 0 ==============================================================================
            auto& scene0 = Engine::SceneManager::Get().CreateScene();

            auto splashScreen = Engine::EntityManager::Get().CreateEntity("SplashScreen");
            splashScreen->GetTransform().Position = sf::Vector2f(512.0f, 384.0f);
            splashScreen->AddComponent<SplashBackground>();
            splashScreen->AddComponent<SplashTitle>();
            splashScreen->AddComponent<SplashController>();

            scene0.AddGameObject(splashScreen);

            // Scene 1 ==============================================================================
            auto& scene1 = Engine::SceneManager::Get().CreateScene();

            auto player = Engine::EntityManager::Get().CreateEntity("Player");
            player->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
            player->AddComponent<Engine::RigidbodyComponent>();
            player->AddComponent<Engine::TriangleComponent>(sf::Color::Blue, 0);
            player->AddComponent<InputComponent>();
            player->AddComponent<ActorComponent>();

            auto enemy = Engine::EntityManager::Get().CreateEntity("Enemy");

            scene1.AddGameObject(player);
            scene1.AddGameObject(enemy);

            Engine::SceneManager::Get().SetActiveScene(scene0.ID);
        }
    };
}


