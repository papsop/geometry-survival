#include "GamePlayScene.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Core/Serializing/SceneSerializer.h>

#include <Engine/Components/UI.h>
#include <Engine/Components/Physics.h>
#include <Engine/Utils/VectorUtils.h>

#include "../Core/GameObject/GameObjectFactory.h"
#include "../Managers/GameManager.h"

#include "../Components/Player/PlayerSpawnerComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Enemy/AIChasePlayerComponent.h"
#include "../Components/Enemy/EnemySpawnerComponent.h"
#include "../Components/Actor/WeaponComponent.h"
#include "../Components/Actor/BulletComponent.h"
#include "../Components/Actor/RPGComponent.h"
#include "../Components/Pickables/ExperienceGlobeComponent.h"
#include "../Components/View/CameraComponent.h"
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
    Engine::PhysicsBodyDef physBodyDef;
    physBodyDef.BodyType = b2_dynamicBody;
    physBodyDef.CategoryBits = 0x1;
    physBodyDef.MaskBits = 0x1;

    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    Engine::CircleFixtureDef circleFixtureDef;
    circleFixtureDef.Radius = 2.0f;

    physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
    physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;

    // ================== Player spawner ==================
    auto* playerSpawner = Engine::GameObjectManager::Get().CreateGameObject("PlayerSpawner", Engine::GameObjectTag::CAMERA, transformDefDefault);
    playerSpawner->AddComponent<PlayerSpawnerComponent>();

    // ================== Camera ==================
    auto* camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
    camera->AddComponent<CameraComponent>(nullptr);

    physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
    physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;

    // ================== Enemy spawner ==================
    auto* enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Enemy spawner", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    enemySpawner->AddComponent<EnemySpawnerComponent>();

    // ================== Activate objects ==================
    camera->SetActive(true);
    enemySpawner->SetActive(true);
    playerSpawner->SetActive(true);

    playerSpawner->GetComponent<PlayerSpawnerComponent>()->CreatePlayerObject();
  }

};