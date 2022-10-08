#include "SplashScreenScene.h"

#include <Engine/Components/Core.h>
#include <Engine/Managers/GameObjectManager.h>
#include "../Components/UI/SplashScreenComponent.h"

namespace Game
{

  void SplashScreenScene::InstantiateObjects() const
  {
    Engine::ITransform::TransformDefinition transformDefDefault; // use default

    // ================== Splash screen ==================
    auto* splashScreen = Engine::GameObjectManager::Get().CreateGameObject("SplashScreen", Engine::GameObjectTag::UNTAGGED, transformDefDefault);
    splashScreen->AddComponent<SplashScreenComponent>();

    // ================== Activate objects ==================
    splashScreen->SetActive(true);
  }

}