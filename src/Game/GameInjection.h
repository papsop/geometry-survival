#pragma once
#include <Engine/Core/ApplicationInjection.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Core/StateMachine/BasicSceneState.h>
#include <Engine/Components/Physics.h>

#include "Components/Player/InputComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/SplashScreen/SplashBackground.h"
#include "Components/SplashScreen/SplashTitle.h"
#include "Components/SplashScreen/SplashController.h"
#include "Components/SplashScreen/SplashShape.h"
#include "Components/Actor/WeaponComponent.h"
#include "Components/Actor/Weapons/PistolWeapon.h"
#include "Components/Actor/BulletComponent.h"


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
            Engine::SubsystemManager::Get().RegisterComponentType<Engine::TriangleComponent>();
            Engine::SubsystemManager::Get().RegisterComponentType<SplashController>();
            Engine::SubsystemManager::Get().RegisterComponentType<InputComponent>();
            Engine::SubsystemManager::Get().RegisterComponentType<WeaponComponent>();
            Engine::SubsystemManager::Get().RegisterComponentType<BulletComponent>();
            Engine::SubsystemManager::Get().RegisterComponentType<ActorComponent>();
        }

        void BeforeGameLoop(Engine::Application& app) override
        {
            // setup logger
            Engine::Logger::Instance().AddBackend(std::make_unique<Engine::ConsoleBackendStrategy>());
            Engine::Logger::Instance().AddBackend(std::make_unique<Engine::WindowBackendStrategy>());
            Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::INFO);

            // Scene 0 ==============================================================================
            auto& scene0 = Engine::SceneManager::Get().CreateScene();
            
            auto splashScreen = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "SplashScreen");
            splashScreen->GetTransform().Position = sf::Vector2f(512.0f, 384.0f);
            splashScreen->AddComponent<SplashBackground>();
            splashScreen->AddComponent<SplashTitle>();
            splashScreen->AddComponent<SplashController>();

            scene0.SetState(std::make_unique<Engine::BasicSceneState>(&scene0));
            scene0.AddGameObject(splashScreen->c_ID);

            // Scene 1 ==============================================================================
            auto& scene1 = Engine::SceneManager::Get().CreateScene();

            auto player = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::PLAYER, "Player");
            player->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
            player->AddComponent<Engine::TriangleComponent>(sf::Color::Blue, 0);
            player->AddComponent<ActorComponent>();
            player->AddComponent<InputComponent>();
            player->AddComponent<WeaponComponent>();

            auto weaponComponent = player->GetComponent<WeaponComponent>();
            weaponComponent->EquipWeapon(std::make_unique<PistolWeapon>(weaponComponent));

            auto enemy = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::ENEMY, "Enemy");
			enemy->AddComponent<Engine::TriangleComponent>(sf::Color::Yellow, 1);
            enemy->AddComponent<ActorComponent>();
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody;
            myBodyDef.position.Set(300, 300);
            enemy->AddComponent<Engine::PhysicsBodyComponent>(&myBodyDef);
            enemy->AddComponent<Engine::CircleFixtureComponent>(50);

            scene1.AddGameObject(player->c_ID);
            scene1.AddGameObject(enemy->c_ID);

            Engine::SceneManager::Get().LoadSceneByIndex(scene1.c_ID);
        }
    };
}


