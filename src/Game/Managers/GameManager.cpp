#include "GameManager.h"
#include <Engine/Debug/Logger.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Engine/Application.h>
#include <Engine/Managers/EventManager.h>
#include <Engine/Managers/SceneManager.h>
#include <Engine/Managers/InputManager.h>

#include "../Core/EventData.h"
#include "../Scenes/GamePlayScene.h"

namespace Game
{
  GameManager::GameManager(Engine::Application& app)
    : m_app(app)
    , m_currentGameState(GameState::Gameplay)
  {
  }

  GameManager* GameManager::Get()
  {
    auto instance = Engine::Application::Instance().GetGameManager<GameManager>();
    DD_ASSERT(instance != nullptr, "GameManager isn't registered with application");
    return instance;
  }

  void GameManager::VirtualOnInit()
  {
    srand((unsigned)time(NULL));

    m_app.GetConfigManager().RegisterCvar("spawner_radius", &m_spawnRadius, 50.0f);
    m_app.GetConfigManager().RegisterCvar("spawner_cooldown", &m_spawnCooldown, 2.0f);
    m_app.GetConfigManager().RegisterCvar("rpg_firstLevelExperience", &m_firstLevelExperience, 50.0f);
  }

  void GameManager::VirtualOnDestroy()
  {
  }

  void GameManager::SetGameState(GameState state)
  {
    switch (state)
    {
    case GameState::Gameplay:
      m_currentGameState = GameState::Gameplay;
      Engine::EventManager::Get().DispatchEvent(event::E_GameResumed());
      break;
    case GameState::Paused:
      m_currentGameState = GameState::Paused;
      Engine::EventManager::Get().DispatchEvent(event::E_GamePaused());
      break;
    default:
      break;
    }
  }

  void GameManager::Update(float dt)
  {
    // TODO: gameManager states
	  if (m_currentGameState == GameState::Gameplay)
	  {
		  m_app.UpdateGameplay(dt);
	  }
	  else if(m_currentGameState == GameState::Paused)
	  {
		  /* */
	  }
  }

  void GameManager::RegisterPlayerGameObject(Engine::GameObject* player)
  {
    m_player = player;
  }

  void GameManager::UnregisterPlayerGameObject()
  {
    m_player = nullptr;
  }

  Engine::GameObject* GameManager::GetPlayerGameObject()
  {
    return m_player;
  }

  Engine::math::Vec2 GameManager::GetRandomEnemySpawnPoint()
  {
    DD_ASSERT(m_player != nullptr, "Cant get enemy spawn without player entity");
    auto playerPos = m_player->GetTransform()->GetAbsoluteTransform().Position;
    Engine::math::Vec2 result;

    float randomAngle = Engine::math::DEG_TO_RAD(rand() % 360);

    result.x = cosf(randomAngle) * m_spawnRadius;
    result.y = sinf(randomAngle) * m_spawnRadius;

    result += playerPos;

    return result;
  }

  // UI Callbacks


  void GameManager::RestartGamePlay()
  {
    Engine::SceneManager::Get().LoadSceneDestroyPrevious(GamePlayScene());
    m_currentGameState = GameState::Gameplay;
  }

  void GameManager::QuitGame()
  { // TODO: add cool effect or something before closing application
    Engine::Application::Instance().Stop();
  }


  // Config
  void GameManager::GetConfigurableData(ConfigurableData& data)
  {
    data.push_back({ "spawner_radius",			std::to_string(m_spawnRadius) });
    data.push_back({ "spawner_cooldown",			std::to_string(m_spawnCooldown) });
    data.push_back({ "rpg_firstLevelExperience",	std::to_string(m_firstLevelExperience) });
  }

  void GameManager::ReceiveEvent(const event::E_OnGameMenu& eventData)
  {
    if (m_currentGameState == GameState::Gameplay && eventData.IsActive)
    {
      m_currentGameState = GameState::Paused;
    }
    else if (m_currentGameState == GameState::Paused && !eventData.IsActive)
    {
      m_currentGameState = GameState::Gameplay;
    }
  }

}
