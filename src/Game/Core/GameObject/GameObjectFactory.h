#pragma once
#include <Engine/Core/GameObject/GameObject.h>

#include "FactoryDefinitions.h"

namespace Game
{
	class GameObjectFactory
	{
	public:
		static Engine::GameObject* CreateEnemy(EnemyFactoryDef def);

		static Engine::GameObject* CreateExperienceGlobe(ExperienceGlobeDef def);
		static Engine::GameObject* CreatePlayerObject(PlayerObjectDef def);
		static Engine::GameObject* CreateBulletObject(BulletFactoryDef def);
		static Engine::GameObject* CreateCombatTextObject(CombatTextDef def);
	};
}