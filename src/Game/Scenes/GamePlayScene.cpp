#include "GamePlayScene.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Managers/GameObjectManager.h>

#include <Engine/Components/Physics.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>

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
#include "../Components/View/BackgroundComponent.h"
#include "../Components/UI/IngameCrosshairComponent.h"
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
		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::BACKGROUND;
		spriteDef.TextureName = "grass_tile";
		//spriteDef.Size = { 128, 72 };
		spriteDef.ShaderName = "background_shader";

		auto* camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
		camera->AddComponent<CameraComponent>(nullptr);
    camera->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		camera->AddComponent<BackgroundComponent>();

    // ================== Enemy spawner ==================
    auto* enemySpawner = Engine::GameObjectManager::Get().CreateGameObject("Enemy spawner", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    enemySpawner->AddComponent<EnemySpawnerComponent>();


    // ================== Crosshair ==================
		spriteDef.Layer = Engine::view::Layer::UI;
		spriteDef.TextureName = "crosshair";
		spriteDef.Size = { 6, 6 };
		spriteDef.ShaderName = "";

    auto* crosshair = Engine::GameObjectManager::Get().CreateGameObject("Crosshair", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    crosshair->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		crosshair->AddComponent<IngameCrosshairComponent>();
		

    // ================== Activate objects ==================
    camera->SetActive(true);
    enemySpawner->SetActive(true);
		playerSpawner->SetActive(true);
		crosshair->SetActive(true);

    playerSpawner->GetComponent<PlayerSpawnerComponent>()->CreatePlayerObject();
  }

};