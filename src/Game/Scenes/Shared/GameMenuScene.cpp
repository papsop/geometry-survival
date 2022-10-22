#include "GameMenuScene.h"
#include <Engine/Managers/GameObjectManager.h>

#include "../../Components/UI/IngameUIComponent.h"
namespace Game
{

  void GameMenuScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Game menu ==================
    auto* gameMenu = Engine::GameObjectManager::Get().CreateGameObject("IngameUI", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    gameMenu->AddComponent<IngameUIComponent>();

    // ================== Activate objects ==================
    gameMenu->SetActive(true);
  }

};
