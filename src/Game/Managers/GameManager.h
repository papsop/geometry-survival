#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Managers/ConfigManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Utils/VectorUtils.h>
#include <Engine/Core/Events.h>
#include <Engine/Debug/IDebuggable.h>

#include "../Core/EventData.h"

#include "GameTimer.h"

namespace Game
{
	// GameState is in EventData

	class GameManager : public Engine::IManager, public Engine::IDebuggable, public Engine::IConfigurable
	{
	public:

		GameManager(Engine::Application& app);
		~GameManager() override = default;

		static GameManager* Get();

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void Update(float dt) override;
		void RegisterPlayerGameObject(Engine::GameObject* player);
		void UnregisterPlayerGameObject();
		Engine::GameObject* GetPlayerGameObject();

		float GetSpawnRadius() { return m_spawnRadius; }
		float GetSpawnCooldown() { return m_spawnCooldown; }
		
		float GetFirstLevelExperience() { return m_firstLevelExperience; }

		GameState GetCurrentGameState() { return m_currentGameState; }
		void SetGameState(GameState state);

		void RestartGamePlay();
		void GoMainMenu();
		void QuitGame();

		void GetConfigurableData(ConfigurableData& data) override;

		GameTimer& GetGameTimer() { return m_gameTimer; }
		GameTimer* GetGameTimerPtr() { return &m_gameTimer; }

		void Debug(Engine::VisualDebugContext& debugContext) override;

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