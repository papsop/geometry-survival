#pragma once

namespace Engine
{
	enum class GameObjectTag 
	{
		UNTAGGED,
		PLAYER,
		ENEMY,
		OBSTACLE,

		// always last
		COUNT
	};
}