#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Utils/VectorUtils.h>

namespace Game
{
	class GameManager : public Engine::IManager
	{
	public:
		GameManager() = default;
		~GameManager() override = default;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void RegisterPlayerGameObject(Engine::GameObject* player);
		void UnregisterPlayerGameObject();
		Engine::GameObject* GetPlayerGameObject();

		Engine::math::Vec2 GetRandomEnemySpawnPoint();
	private:
		Engine::GameObject* m_player;
		float m_spawnRadius = 40.0f;
	};
}