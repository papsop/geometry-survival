#include "MainMenuScene.h"

#include "../Components/UI/MainMenuScreenComponent.h"


#include <Engine/Managers/GameObjectManager.h>
namespace Game
{

  void MainMenuScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Main menu ==================
    auto* mainMenu = Engine::GameObjectManager::Get().CreateGameObject("MainMenu", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    mainMenu->AddComponent<MainMenuScreenComponent>();

    // ================== Activate objects ==================
    mainMenu->SetActive(true);
  }

}