#include "MainMenuScene.h"

#include "../Components/UI/MainMenuScreenComponent.h"
#include "../Components/UI/SettingsScreenComponent.h"
#include "../Components/UI/Controllers/MainMenuUIControllerComponent.h"

#include "../Components/View/CameraComponent.h"
#include "../Components/View/BackgroundComponent.h"

#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Managers/GameObjectManager.h>
namespace Game
{

  void MainMenuScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Main menu ==================
    auto* mainMenu = Engine::GameObjectManager::Get().CreateGameObject("MainMenu", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    mainMenu->AddComponent<MainMenuScreenComponent>();
    mainMenu->AddComponent<SettingsScreenComponent>();
    mainMenu->AddComponent<MainMenuUIControllerComponent>();

		// ================== Camera ==================
		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::BACKGROUND;
		spriteDef.TextureName = "grass_tile";
		spriteDef.Size = { 128, 72 };
		spriteDef.ShaderName = "background_shader";

		auto* camera = Engine::GameObjectManager::Get().CreateGameObject("MainCamera", Engine::GameObjectTag::CAMERA, transformDefDefault);
		camera->AddComponent<CameraComponent>(nullptr);
		camera->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		camera->AddComponent<BackgroundComponent>();
    // ================== Activate objects ==================

    mainMenu->SetActive(true);
		camera->SetActive(true);
  }

}