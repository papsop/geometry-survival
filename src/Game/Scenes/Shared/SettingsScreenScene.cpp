#include "SettingsScreenScene.h"
#include <Engine/Managers/GameObjectManager.h>

#include "../../Components/UI/GameMenuComponent.h"

namespace Game
{

  void SettingsScreenScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Game menu ==================
    auto* gameMenu = Engine::GameObjectManager::Get().CreateGameObject("GameMenu", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    gameMenu->AddComponent<GameMenuComponent>();

    // ================== Activate objects ==================
    gameMenu->SetActive(false); // game menu should be disabled by default
  }

};
