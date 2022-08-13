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
#include "Components/Player/PlayerComponent.h"
#include "Components/Player/PickUpFieldComponent.h"
#include "Components/Player/LevelComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/Actor/RPGComponent.h"
#include "Components/Enemy/AIChaseTargetComponent.h"
#include "Components/Enemy/EasyEnemySpawnerComponent.h"
#include "Components/SplashScreen/SplashBackground.h"
#include "Components/SplashScreen/SplashTitle.h"
#include "Components/SplashScreen/SplashController.h"
#include "Components/SplashScreen/SplashShape.h"
#include "Components/Actor/WeaponComponent.h"
#include "Components/Actor/Weapons/PistolWeapon.h"
#include "Components/Actor/BulletComponent.h"
#include "Components/Actor/RPGComponent.h"
#include "Components/Pickables/ExperienceGlobeComponent.h"
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
			Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::INFO);

            // Order is important
            Engine::ComponentManager::Get().RegisterComponentType<SplashShape>();
            Engine::ComponentManager::Get().RegisterComponentType<SplashController>();
            Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<AIChaseTargetComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ExperienceGlobeComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<RPGComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<EasyEnemySpawnerComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<LevelComponent>();

            Engine::Application::Instance().RegisterGameManager<GameManager>();
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

            Engine::CircleFixtureDef circleFixtureDef;
            circleFixtureDef.Radius = 2.0f;
            shapeViewDef.Layer = Engine::view::Layer::PLAYER;

			physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
			physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;
            auto player = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::PLAYER);
            player->GetTransform().SetPosition({ 5.0f, 0.0f });
            player->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
            player->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
            player->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);

            RPGActorDef rpgActorDef;
            rpgActorDef.MaxHealth = 5;
            rpgActorDef.AttackSpeed = 100.0f;
            rpgActorDef.WeaponDamage = 100.0f;
            rpgActorDef.MovementSpeed = 20.0f;
            player->AddComponent<RPGComponent>(rpgActorDef);
            player->AddComponent<ActorComponent>();
            player->AddComponent<PickUpFieldComponent>();
            player->AddComponent<InputComponent>();
            player->AddComponent<WeaponComponent>();
            auto weaponComp = player->GetComponent<WeaponComponent>();
            weaponComp->EquipWeapon(std::make_unique<PistolWeapon>(*weaponComp));
            player->AddComponent<PlayerComponent>();
            player->AddComponent<LevelComponent>();

			auto camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA);
            camera->AddComponent<Engine::CameraComponent>(player);

            // buff test
//             std::unique_ptr<Buff> buff = std::make_unique<Buff>(5.0f);
//             buff->AddModifier(RPGStats::MAX_HEALTH, 20)
//                  .AddModifier(RPGStats::MOVEMENT_SPEED, 30);

            //player->GetComponent<ActorComponent>()->GetRPGActor()->AddBuff(std::move(buff));
            // test buff
            //auto rpgactor = player->GetComponent<ActorComponent>()->GetRPGActor();
            //rpgactor.AddBuff(std::make_unique<Buff>(5.0f));
            // ---------

            physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
            physBodyDef.MaskBits= physics::EntityMask::M_ENEMY;
            shapeViewDef.Color = sf::Color::Red;

            //enemy spawner
            auto enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::UNTAGGED);
            enemySpawner->AddComponent<EasyEnemySpawnerComponent>();

            // walls
            //WallFactoryDef wallFactoryDef;
            //wallFactoryDef.Position = { 0.5f, 0.5f };
            //wallFactoryDef.Size = { 100.0f, .5f };
            //wallFactoryDef.RotationDeg = 90.0f;
            //auto wall1 = GameObjectFactory::CreateWall(wallFactoryDef);
            //wallFactoryDef.Position = { 0.0f, 5.0f };
            //wallFactoryDef.RotationDeg = 270.0f;
            //auto wall2 = GameObjectFactory::CreateWall(wallFactoryDef);
            //wallFactoryDef.Position = { 0.0f, 2.5f };
            //wallFactoryDef.RotationDeg = 0.0f;
            //auto wall3 = GameObjectFactory::CreateWall(wallFactoryDef);

            

           // scene1.AddGameObject(centerCamera->ID);
            scene1.AddGameObject(player->ID);
            scene1.AddGameObject(enemySpawner->ID);
            scene1.AddGameObject(camera->ID);
			//scene1.AddGameObject(wall2->ID);
			//scene1.AddGameObject(wall3->ID);

            Engine::SceneManager::Get().LoadSceneByIndex(scene1.ID);
        }
    };
}


