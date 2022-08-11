#include "GameManager.h"
#include <Engine/Debug/Logger.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Engine/Managers/ConfigManager.h>
namespace Game
{
	void GameManager::VirtualOnInit()
	{
		srand((unsigned)time(NULL));

		Engine::ConfigManager::Get().RegisterCvar("spawner_radius", &m_spawnRadius, 50.0f);
		Engine::ConfigManager::Get().RegisterCvar("spawner_cooldown", &m_spawnCooldown, 2.0f);
	}

	void GameManager::VirtualOnDestroy()
	{
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
		auto playerPos = m_player->GetTransform().Position;
		Engine::math::Vec2 result;

		float randomAngle = Engine::math::DEG_TO_RAD(rand() % 360);

		result.x = cosf(randomAngle) * m_spawnRadius;
		result.y = sinf(randomAngle) * m_spawnRadius;

		result += playerPos;

		return result;
	}

}
