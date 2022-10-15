#pragma once
#include <Engine/Core/GameObject/GameObject.h>

#include "FactoryDefinitions.h"

namespace Game
{
	class GameObjectFactory
	{
	public:
		static Engine::GameObject* CreateWall(const WallFactoryDef& def);
		static Engine::GameObject* CreateEnemy(const EnemyFactoryDef& def);
		static Engine::GameObject* CreateExperienceGlobe(const ExperienceGlobeDef& def);
		static Engine::GameObject* CreatePlayerObject(const PlayerObjectDef& def);
	};
}