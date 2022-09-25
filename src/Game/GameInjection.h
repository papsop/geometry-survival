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
#include "Components/UI/ExperienceBarComponent.h"
#include "Components/UI/AmmoHUDComponent.h"
#include "Components/UI/LevelHUDComponent.h"
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
      Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<AIChaseTargetComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<ExperienceGlobeComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<RPGComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<EasyEnemySpawnerComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<LevelComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<ExperienceBarComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<AmmoHUDComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<LevelHUDComponent>();
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


      physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
      physBodyDef.MaskBits= physics::EntityMask::M_ENEMY;
      shapeViewDef.Color = sf::Color::Red;

		  Engine::ShapeViewDef shapeViewDef2;
		  shapeViewDef2.Color = sf::Color::Magenta;
		  shapeViewDef2.PointCount = 7;
		  shapeViewDef2.Radius = 25.0f;

      // =======================================================================================
      // UI
      // =======================================================================================
      Engine::ITransform::TransformDefinition transformDefUI;
      transformDefUI.TransType = Engine::ITransform::TransformType::RectTransform;
      transformDefUI.Anchor = Engine::RectAnchor::TopLeft;
		  transformDefUI.Position = { 0.0f, 0.0f };
      transformDefUI.Size = app.GetViewManager().GetResolution(); // UI canvas is always full window size
      transformDefUI.Space = Engine::ITransform::PositionSpace::CameraSpace;
      transformDefUI.PosType = Engine::ITransform::PositionType::Absolute;
      auto* UICanvas = Engine::GameObjectManager::Get().CreateGameObject("Canvas", Engine::GameObjectTag::UNTAGGED, transformDefUI);

      // ================== Experience bar HUD ==================
      transformDefUI.PosType = Engine::ITransform::PositionType::Relative;
      transformDefUI.Anchor = Engine::RectAnchor::TopLeft;
      auto* expBarWrapper = Engine::GameObjectManager::Get().CreateGameObject("Experience bar wrapper", Engine::GameObjectTag::UNTAGGED, transformDefUI);
      if (auto* expBarWrapperTrans = expBarWrapper->GetTransformAs<Engine::RectTransform>())
      {
          expBarWrapperTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Width, Engine::RelativeConstraint(1.0f));
          expBarWrapperTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Height, Engine::RelativeConstraint(.025f));

          // set same size for bar for now
          transformDefUI.Size = expBarWrapperTrans->GetSize();
      }
      Engine::RectangleViewDef rectangleDef;
      rectangleDef.Color = sf::Color::Yellow;
      rectangleDef.Layer = Engine::view::Layer::UI;
      auto* expBar = Engine::GameObjectManager::Get().CreateGameObject("Experience bar", Engine::GameObjectTag::UNTAGGED, transformDefUI);
      expBarWrapper->GetTransform()->AddChild(expBar);
      expBar->AddComponent<ExperienceBarComponent>();
      expBar->AddComponent<Engine::RectangleViewComponent>(rectangleDef);


      // ================== Ammo HUD ==================
      transformDefUI.Anchor = Engine::RectAnchor::BottomRight;
      auto* ammoHUD = Engine::GameObjectManager::Get().CreateGameObject("Ammo HUD", Engine::GameObjectTag::UNTAGGED, transformDefUI);
      if (auto* ammoHUDRectTrans= ammoHUD->GetTransformAs<Engine::RectTransform>())
      {
        ammoHUDRectTrans->SetConstraint(Engine::RectTransform::ConstraintParam::X, Engine::RelativeConstraint(.95f));
        ammoHUDRectTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Y, Engine::RelativeConstraint(1.0f));
        ammoHUDRectTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Width, Engine::RelativeConstraint(.15f));
        ammoHUDRectTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Height, Engine::RelativeConstraint(.10f));
      }
      ammoHUD->AddComponent<AmmoHUDComponent>();
      Engine::TextViewDef textDef;
      textDef.ShouldCenter = false;
      textDef.FontSize = 42;
      ammoHUD->AddComponent<Engine::TextViewComponent>(textDef);

      // ================== Level HUD ==================
      transformDefUI.Anchor = Engine::RectAnchor::BottomLeft;
      auto* levelHUD = Engine::GameObjectManager::Get().CreateGameObject("Level HUD", Engine::GameObjectTag::UNTAGGED, transformDefUI);
      if (auto* levelHUDTrans = levelHUD->GetTransformAs<Engine::RectTransform>())
      {
        levelHUDTrans->SetConstraint(Engine::RectTransform::ConstraintParam::X, Engine::RelativeConstraint(.02f));
        levelHUDTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Y, Engine::RelativeConstraint(1.0f));
        levelHUDTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Width, Engine::RelativeConstraint(.15f));
        levelHUDTrans->SetConstraint(Engine::RectTransform::ConstraintParam::Height, Engine::RelativeConstraint(.10f));
      }
      levelHUD->AddComponent<LevelHUDComponent>();
      textDef.ShouldCenter = false;
      textDef.FontSize = 42;
      levelHUD->AddComponent<Engine::TextViewComponent>(textDef);


      // ================== Hierarchy HUD ==================
      UICanvas->GetTransform()->AddChild(expBarWrapper);
      UICanvas->GetTransform()->AddChild(ammoHUD);
      UICanvas->GetTransform()->AddChild(ammoHUD);
      UICanvas->GetTransform()->AddChild(levelHUD);
      
      // ================== Enemy spawner ==================
      auto enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Enemy spawner", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
      enemySpawner->AddComponent<EasyEnemySpawnerComponent>();

      // scene1.AddGameObject(centerCamera->ID);
      scene1.AddGameObject(player->ID);
      scene1.AddGameObject(enemySpawner->ID);
      scene1.AddGameObject(camera->ID);
      scene1.AddGameObject(UICanvas->ID);
      scene1.AddGameObject(expBar->ID);
      scene1.AddGameObject(expBarWrapper->ID);
      scene1.AddGameObject(ammoHUD->ID);
      scene1.AddGameObject(levelHUD->ID);
      //scene1.AddGameObject(wall2->ID);
	    //scene1.AddGameObject(wall3->ID);

      Engine::SceneManager::Get().LoadSceneByIndex(scene1.ID);

      //UICanvas->Destroy();
    }
  };
}


