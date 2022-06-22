#pragma once

namespace Engine
{
	enum class GameObjectTag 
	{
		UNTAGGED,
		PLAYER,
		PLAYER_BULLET,
		ENEMY,
		OBSTACLE,

		// always last
		COUNT
	};
}