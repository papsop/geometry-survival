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

}
