#include "GameManager.h"
#include <Engine/Debug/Logger.h>

namespace Game
{
	void GameManager::VirtualOnInit()
	{
		LOG_WARN("GameManager::VirtualOnInit()");
	}

	void GameManager::VirtualOnDestroy()
	{
		LOG_WARN("GameManager::VirtualOnDestroy()");
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

}
