#pragma once
#include <Engine/Core/GameObject/GameObject.h>

#include "FactoryDefinitions.h"

namespace Game
{
	class GameObjectFactory
	{
	public:
		static Engine::GameObject* CreateWall(const WallFactoryDef& def);
	};
}