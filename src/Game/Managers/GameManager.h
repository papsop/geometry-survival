#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Managers/ConfigManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Utils/VectorUtils.h>
#include <Engine/Core/Events.h>

#include "../Core/EventData.h"

#include "GameTimer.h"

namespace Game
{
	class GameManager : public Engine::IManager, public Engine::IConfigurable
	{
	public:
		enum class GameState
		{
			Gameplay,
			Paused
		};

		GameManager(Engine::Application& app);
		~GameManager() override = default;

		static GameManager* Get();

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void Update(float dt) override;
		void RegisterPlayerGameObject(Engine::GameObject* player);
		void UnregisterPlayerGameObject();
		Engine::GameObject* GetPlayerGameObject();

		Engine::math::Vec2 GetRandomEnemySpawnPoint();

		float GetSpawnRadius() { return m_spawnRadius; }
		float GetSpawnCooldown() { return m_spawnCooldown; }
		GameState GetCurrentGameState() { return m_currentGameState; }
		float GetFirstLevelExperience() { return m_firstLevelExperience; }

		void SetGameState(GameState state);

		void RestartGamePlay();
		void GoMainMenu();
		void QuitGame();

		void GetConfigurableData(ConfigurableData& data) override;

		GameTimer& GetGameTimer() { return m_gameTimer; }

	private:
		void SendPlayerRegistrationEvent(bool registered);

		Engine::GameObject* m_player = nullptr;
		GameTimer m_gameTimer;

		float m_spawnRadius;
		float m_spawnCooldown;
		float m_firstLevelExperience;

		Engine::Application& m_app;
		GameState m_currentGameState;
	};
}