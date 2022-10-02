#include "GamePlayScene.h"

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

#include "../Core/GameObject/GameObjectFactory.h"
#include "../Managers/GameManager.h"

#include "../Components/Player/InputComponent.h"
#include "../Components/Player/PlayerComponent.h"
#include "../Components/Player/PickUpFieldComponent.h"
#include "../Components/Player/LevelComponent.h"
#include "../Components/Actor/ActorComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Enemy/AIChaseTargetComponent.h"
#include "../Components/Enemy/EasyEnemySpawnerComponent.h"
#include "../Components/Actor/WeaponComponent.h"
#include "../Components/Actor/Weapons/PistolWeapon.h"
#include "../Components/Actor/BulletComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Pickables/ExperienceGlobeComponent.h"
#include "../Physics/Filters.h"

namespace Game
{
  
  void GamePlayScene::InstantiateScene() const
  {
    Engine::ShapeViewDef shapeViewDef;
    shapeViewDef.Color = sf::Color::Green;
    shapeViewDef.PointCount = 3;
    shapeViewDef.Radius = 2;

    Engine::PhysicsBodyDef physBodyDef;
    physBodyDef.BodyType = b2_dynamicBody;
    physBodyDef.CategoryBits = 0x1;
    physBodyDef.MaskBits = 0x1;

    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    Engine::CircleFixtureDef circleFixtureDef;
    circleFixtureDef.Radius = 2.0f;
    shapeViewDef.Layer = Engine::view::Layer::PLAYER;

    physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
    physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;

    // ================== Player ==================
    auto* player = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::PLAYER, transformDefDefault);
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
    auto* weaponComp = player->GetComponent<WeaponComponent>();
    weaponComp->EquipWeapon(std::make_unique<PistolWeapon>(*weaponComp));
    player->AddComponent<PlayerComponent>();
    player->AddComponent<LevelComponent>();

    // ================== Camera ==================
    auto* camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
    camera->AddComponent<Engine::CameraComponent>(player);

    physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
    physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;
    shapeViewDef.Color = sf::Color::Red;

    Engine::ShapeViewDef shapeViewDef2;
    shapeViewDef2.Color = sf::Color::Magenta;
    shapeViewDef2.PointCount = 7;
    shapeViewDef2.Radius = 25.0f;

    // ================== Enemy spawner ==================
    auto* enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Enemy spawner", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    enemySpawner->AddComponent<EasyEnemySpawnerComponent>();
  }

};