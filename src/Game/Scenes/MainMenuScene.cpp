#include "MainMenuScene.h"

#include "../Components/UI/MainMenuScreenComponent.h"


#include <Engine/Managers/GameObjectManager.h>
namespace Game
{

  void MainMenuScene::InstantiateScene() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Player ==================
    auto* mainMenu = Engine::GameObjectManager::Get().CreateGameObject("MainMenu", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    mainMenu->AddComponent<MainMenuScreenComponent>();
  }

}