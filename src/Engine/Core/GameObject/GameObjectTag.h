#pragma once

namespace Engine
{
	enum class GameObjectTag 
	{
		UNTAGGED = 0x0,
		PLAYER = 0x1,
		PLAYER_BULLET = 0x2,
		ENEMY = 0x4,
		OBSTACLE = 0x8,

		// always last
		COUNT
	};
	
	inline GameObjectTag operator|(GameObjectTag a, GameObjectTag b)
	{
		return (GameObjectTag)((int)a | (int)b);
	}

	static inline bool HasGameObjectTagFlag(GameObjectTag a, GameObjectTag b)
	{
		return (static_cast<int>(a) & static_cast<int>(b)) > 0;
	}
}