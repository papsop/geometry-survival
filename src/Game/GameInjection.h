#pragma once
#include <Engine/Core/ApplicationInjection.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Core/StateMachine/BasicSceneState.h>
#include <Engine/Core/Serializing/SceneSerializer.h>

#include <Engine/Components/View.h>
#include <Engine/Components/UI.h>
#include <Engine/Components/Physics.h>
#include <Engine/Utils/VectorUtils.h>

#include <Engine/Components/UI/LayoutElementComponent.h>
#include <Engine/Components/UI/HorizontalLayoutComponent.h>
#include <Engine/Components/UI/VerticalLayoutComponent.h>

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
			Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::DEBUG);

            // Order is important
            Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<AIChaseTargetComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ExperienceGlobeComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<RPGComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<EasyEnemySpawnerComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<LevelComponent>();
            // TODO: shouldnt be here, handle in UI manager?
            Engine::ComponentManager::Get().RegisterComponentType<Engine::HorizontalLayoutComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<Engine::VerticalLayoutComponent>();

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

            Engine::ITransform::TransformDefinition transformDefDefault; // use default
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
            auto player = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::PLAYER, transformDefDefault);
            player->GetTransform()->SetPosition({ 5.0f, 0.0f });
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

			auto camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
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
            auto enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Enemy spawner", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
            enemySpawner->AddComponent<EasyEnemySpawnerComponent>();

			Engine::ShapeViewDef shapeViewDef2;
			shapeViewDef2.Color = sf::Color::Magenta;
			shapeViewDef2.PointCount = 7;
			shapeViewDef2.Radius = 25.0f;

            Engine::ITransform::TransformDefinition transformDefUI;
            transformDefUI.TransType = Engine::ITransform::TransformType::RectTransform;
            transformDefUI.Anchor = Engine::RectAnchor::TopLeft;
            transformDefUI.Size = { 50.0f, 50.0f, };
            transformDefUI.Position = { 50.0f, 50.0f };
            transformDefUI.Space = Engine::ITransform::PositionSpace::CameraSpace;
            transformDefUI.PosType = Engine::ITransform::PositionType::Absolute;
            
            auto sub_ui_1 = Engine::GameObjectManager::Get().CreateGameObject("TestUI", Engine::GameObjectTag::UNTAGGED, transformDefUI);
            sub_ui_1->AddComponent<Engine::LayoutElementComponent>();
            transformDefUI.Position = { 150.0f, 50.0f };
			auto sub_ui_2 = Engine::GameObjectManager::Get().CreateGameObject("TestUI2", Engine::GameObjectTag::UNTAGGED, transformDefUI);
            sub_ui_2->AddComponent<Engine::LayoutElementComponent>();
            transformDefUI.Position = { 250.0f, 50.0f };
			auto sub_ui_3 = Engine::GameObjectManager::Get().CreateGameObject("TestUI3", Engine::GameObjectTag::UNTAGGED, transformDefUI);
            sub_ui_3->AddComponent<Engine::LayoutElementComponent>();
			auto sub_ui_4 = Engine::GameObjectManager::Get().CreateGameObject("TestUI3", Engine::GameObjectTag::UNTAGGED, transformDefUI);
			sub_ui_4->AddComponent<Engine::LayoutElementComponent>();
			auto sub_ui_5 = Engine::GameObjectManager::Get().CreateGameObject("TestUI3", Engine::GameObjectTag::UNTAGGED, transformDefUI);
			sub_ui_5->AddComponent<Engine::LayoutElementComponent>();

            transformDefUI.Position = { 500.0f, 0.0f };
            transformDefUI.Size = { 250.0f, 100.0f, };
            transformDefUI.Anchor = Engine::RectAnchor::TopCenter;
            auto layouter = Engine::GameObjectManager::Get().CreateGameObject("Layouter", Engine::GameObjectTag::UNTAGGED, transformDefUI);
            layouter->GetTransform()->SetChild(sub_ui_1);
            layouter->GetTransform()->SetChild(sub_ui_2);
            layouter->GetTransform()->SetChild(sub_ui_3);
            layouter->GetTransform()->SetChild(sub_ui_4);
            layouter->GetTransform()->SetChild(sub_ui_5);
            layouter->AddComponent<Engine::HorizontalLayoutComponent>();

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
            scene1.AddGameObject(layouter->ID);
            scene1.AddGameObject(sub_ui_1->ID);
            scene1.AddGameObject(sub_ui_2->ID);
            scene1.AddGameObject(sub_ui_3->ID);
			//scene1.AddGameObject(wall2->ID);
			//scene1.AddGameObject(wall3->ID);

            Engine::SceneManager::Get().LoadSceneByIndex(scene1.ID);
        }
    };
}


