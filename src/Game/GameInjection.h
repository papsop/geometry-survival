#pragma once
#include <Engine/Core/ApplicationInjection.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Debug/Backend/ImGuiBackendStrategy.h>

#include <Engine/Managers/SceneManager.h>
#include <Engine/Managers/ComponentManager.h>

#include <Engine/Components/Physics.h>
#include <Engine/Utils/VectorUtils.h>
#include "Core/GameObject/GameObjectFactory.h"

#include "Managers/GameManager.h"
#include "Managers/SkillsManager.h"
#include "Managers/EnemySpawningManager.h"

#include "Components/Player/InputComponent.h"
#include "Components/Player/PlayerComponent.h"
#include "Components/Player/PickUpFieldComponent.h"
#include "Components/Player/LevelComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/Actor/RPGComponent.h"
#include "Components/Enemy/AIChasePlayerComponent.h"
#include "Components/Actor/WeaponComponent.h"
#include "Components/Actor/BulletComponent.h"
#include "Components/Actor/RPGComponent.h"
#include "Components/Actor/DestroyAfterTimeComponent.h"
#include "Components/Pickables/ExperienceGlobeComponent.h"
#include "Components/Pickables/PickableItemComponent.h"
#include "Components/UI/SplashScreenComponent.h"
#include "Components/UI/IngameCrosshairComponent.h"
#include "Components/View/CameraComponent.h"
#include "Components/View/CombatTextComponent.h"
#include "Components/View/BackgroundComponent.h"

#include "Scenes/GamePlayScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/SplashScreenScene.h"


namespace Game
{
  class Engine::Application;
  class GameInjection : public Engine::ApplicationInjection
  {
  public:
    void RegisterGameComponents(Engine::Application& app) override
    {

    }

    void BeforeGameLoop(Engine::Application& app) override
    {
      // Setup logger
      Engine::Logger::Instance().AddBackend(std::make_unique<Engine::ConsoleBackendStrategy>());
      Engine::Logger::Instance().AddBackend(std::make_unique<Engine::ImGuiBackendStrategy>());
      Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::ERROR);

      // Setup components
      //  - order is important because of updates
      //  - only components that need to be updated should be placed here
      //  - components without update are still usable, just won't get updated
      Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<CameraComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<DestroyAfterTimeComponent>();
			Engine::ComponentManager::Get().RegisterComponentType<ExperienceGlobeComponent>();
			Engine::ComponentManager::Get().RegisterComponentType<PickableItemComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<RPGComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<EnemyComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<SplashScreenComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<CombatTextComponent>();
      Engine::ComponentManager::Get().RegisterComponentType<PickUpFieldComponent>();
			Engine::ComponentManager::Get().RegisterComponentType<BackgroundComponent>();
			Engine::ComponentManager::Get().RegisterComponentType<IngameCrosshairComponent>();
			Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();

      // Custom game managers
      Engine::Application::Instance().RegisterGameManager<GameManager>();
      Engine::Application::Instance().RegisterGameManager<SkillsManager>();
      Engine::Application::Instance().RegisterGameManager<EnemySpawningManager>();
    
      // First scene after starting application
      //app.GetSceneManager().LoadSceneDestroyPrevious(SplashScreenScene());
      app.GetSceneManager().LoadSceneDestroyPrevious(MainMenuScene());
    }
  };
}