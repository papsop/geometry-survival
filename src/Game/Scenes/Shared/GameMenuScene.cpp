#include "GameMenuScene.h"
#include <Engine/Managers/GameObjectManager.h>

#include "../../Components/UI/IngameHUDComponent.h"
#include "../../Components/UI/IngameMenuComponent.h"
#include "../../Components/UI/SettingsScreenComponent.h"
#include "../../Components/UI/IngameUIControllerComponent.h"
#include "../../Components/UI/SkillPickerScreenComponent.h"
namespace Game
{

  void GameMenuScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Game menu ==================
    auto* gameMenu = Engine::GameObjectManager::Get().CreateGameObject("IngameUI", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    gameMenu->AddComponent<IngameMenuComponent>();
    gameMenu->AddComponent<SkillPickerScreenComponent>();
    gameMenu->AddComponent<IngameHUDComponent>();
    gameMenu->AddComponent<SettingsScreenComponent>();
    gameMenu->AddComponent<IngameUIControllerComponent>();

    // ================== Activate objects ==================
    gameMenu->SetActive(true);
  }

};
