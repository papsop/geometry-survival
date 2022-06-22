#pragma once
#include <Engine/Core/ApplicationInjection.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Core/StateMachine/BasicSceneState.h>
#include <Engine/Core/Serializing/SceneSerializer.h>

#include <Engine/Components/View.h>
#include <Engine/Components/Physics.h>
#include <Engine/Utils/VectorUtils.h>

#include "Core/GameObject/GameObjectFactory.h"
#include "Managers/GameManager.h"

#include "Components/Player/InputComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/Enemy/AIChaseTargetComponent.h"
#include "Components/SplashScreen/SplashBackground.h"
#include "Components/SplashScreen/SplashTitle.h"
#include "Components/SplashScreen/SplashController.h"
#include "Components/SplashScreen/SplashShape.h"
#include "Components/Actor/WeaponComponent.h"
#include "Components/Actor/Weapons/PistolWeapon.h"
#include "Components/Actor/BulletComponent.h"
#include "Physics/Filters.h"

namespace Game
{
    class Engine::Application;
    class GameInjection : public Engine::ApplicationInjection
    {
    public:
        void RegisterGameComponents(Engine::Application& app) override
        {
			// setup logger
			Engine::Logger::Instance().AddBackend(std::make_unique<Engine::ConsoleBackendStrategy>());
			Engine::Logger::Instance().AddBackend(std::make_unique<Engine::WindowBackendStrategy>());
			Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::DEBUG);

            // Order is important
            Engine::ComponentManager::Get().RegisterComponentType<SplashShape>();
            Engine::ComponentManager::Get().RegisterComponentType<SplashController>();
            Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<AIChaseTargetComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();

            Engine::Application::Instance().RegisterManager<GameManager>();
        }

        void BeforeGameLoop(Engine::Application& app) override
        {

            // Scene 0 ==============================================================================
            //auto& scene0 = Engine::SceneManager::Get().CreateScene();
            //
            //auto splashScreen = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "SplashScreen");
            //splashScreen->GetTransform().Position = sf::Vector2f(512.0f, 384.0f);
            //splashScreen->AddComponent<SplashBackground>();
            //splashScreen->AddComponent<SplashTitle>();
            //splashScreen->AddComponent<SplashController>();

            //scene0.SetState(std::make_unique<Engine::BasicSceneState>(&scene0));
            //scene0.AddGameObject(splashScreen->ID);

            Engine::ShapeViewDef shapeViewDef;
            shapeViewDef.Color = sf::Color::Green;
            shapeViewDef.PointCount = 3;
            shapeViewDef.Radius = 2;

            Engine::PhysicsBodyDef physBodyDef;
            physBodyDef.BodyType = b2_dynamicBody;
            physBodyDef.CategoryBits = 0x1;
            physBodyDef.MaskBits = 0x1;

            // Scene 1 ==============================================================================
            auto& scene1 = Engine::SceneManager::Get().CreateScene();

            //auto centerCamera = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "MainCamera");
            //centerCamera->GetTransform().SetPosition({ 0.0f, 0.0f });
            //centerCamera->AddComponent<Engine::CameraComponent>();

			physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
			physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;
            auto player = Engine::GameObjectManager::Get().CreateGameObject("Player");
            player->GetTransform().SetPosition({ 5.0f, 0.0f });
            player->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
            player->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
            player->AddComponent<Engine::CircleFixtureComponent>(2.0f);
            player->AddComponent<ActorComponent>(15.0f);
            player->AddComponent<InputComponent>();
            player->AddComponent<WeaponComponent>();
            auto weaponComp = player->GetComponent<WeaponComponent>();
            weaponComp->EquipWeapon(std::make_unique<PistolWeapon>(weaponComp));
            player->AddComponent<Engine::CameraComponent>();

            physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
            physBodyDef.MaskBits= physics::EntityMask::M_ENEMY;
            shapeViewDef.Color = sf::Color::Red;

            for (size_t i = 0; i < 1; i++)
            {
				EnemyFactoryDef enemyFactoryDef;
				enemyFactoryDef.MovementSpeed = 3.0f;
				enemyFactoryDef.Player = player;
				enemyFactoryDef.Position = { 10.0f + (i * 5), 10.0f + (powf(-1.0f, i) * 3)};
				auto enemyObj = GameObjectFactory::CreateEnemy(enemyFactoryDef);
                scene1.AddGameObject(enemyObj->ID);
            }

            

            // walls
            WallFactoryDef wallFactoryDef;
            wallFactoryDef.Position = { 0.5f, 0.5f };
            wallFactoryDef.Size = { 100.0f, .5f };
            wallFactoryDef.RotationDeg = 90.0f;
            auto wall1 = GameObjectFactory::CreateWall(wallFactoryDef);
            //wallFactoryDef.Position = { 0.0f, 5.0f };
            //wallFactoryDef.RotationDeg = 270.0f;
            //auto wall2 = GameObjectFactory::CreateWall(wallFactoryDef);
            //wallFactoryDef.Position = { 0.0f, 2.5f };
            //wallFactoryDef.RotationDeg = 0.0f;
            //auto wall3 = GameObjectFactory::CreateWall(wallFactoryDef);

            

           // scene1.AddGameObject(centerCamera->ID);
            scene1.AddGameObject(player->ID);
            scene1.AddGameObject(wall1->ID);
			//scene1.AddGameObject(wall2->ID);
			//scene1.AddGameObject(wall3->ID);

            Engine::SceneManager::Get().LoadSceneByIndex(scene1.ID);
        }
    };
}


