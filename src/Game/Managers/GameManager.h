#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Managers/ConfigManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Utils/VectorUtils.h>
#include <Engine/Core/Events.h>
#include "../Core/EventData.h"

namespace Game
{
	class GameManager : public Engine::IManager, public Engine::IConfigurable, public Engine::IEventListener<event::E_OnGameMenu>
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
		void QuitGame();

		void GetConfigurableData(ConfigurableData& data) override;

	protected:
		void ReceiveEvent(const event::E_OnGameMenu& eventData) override;

	private:
		Engine::GameObject* m_player;
		float m_spawnRadius;
		float m_spawnCooldown;
		float m_firstLevelExperience;

		Engine::Application& m_app;
		GameState m_currentGameState;
	};
}