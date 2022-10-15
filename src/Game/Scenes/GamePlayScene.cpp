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

#include "../Components/Player/PlayerSpawnerComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Enemy/AIChaseTargetComponent.h"
#include "../Components/Enemy/EasyEnemySpawnerComponent.h"
#include "../Components/Actor/WeaponComponent.h"
#include "../Components/Actor/Weapons/PistolWeapon.h"
#include "../Components/Actor/BulletComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Pickables/ExperienceGlobeComponent.h"
#include "../Physics/Filters.h"


#include "Shared/GameMenuScene.h"

namespace Game
{
  
  void GamePlayScene::InstantiateObjects() const
  {

    // ================== Shared scenes ==================
    GameMenuScene gameMenuScene;
    gameMenuScene.InstantiateObjects();

    // ===================================================

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

    // ================== Player spawner ==================
    auto* playerSpawner = Engine::GameObjectManager::Get().CreateGameObject("PlayerSpawner", Engine::GameObjectTag::CAMERA, transformDefDefault);
    playerSpawner->AddComponent<PlayerSpawnerComponent>();

    // ================== Camera ==================
    auto* camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
    camera->AddComponent<Engine::CameraComponent>(nullptr);

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

    // ================== Activate objects ==================
    camera->SetActive(true);
    enemySpawner->SetActive(true);
    playerSpawner->SetActive(true);
  }

};