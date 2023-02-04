#include "MainMenuScene.h"

#include "../Components/UI/MainMenuScreenComponent.h"
#include "../Components/UI/SettingsScreenComponent.h"
#include "../Components/UI/Controllers/MainMenuUIControllerComponent.h"


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

    // ================== Activate objects ==================
    mainMenu->SetActive(true);
  }

}