#pragma once

namespace Engine
{
	enum class GameObjectTag 
	{
		UNTAGGED			= 0x0001,
		PLAYER				= 0x0002,
		PLAYER_BULLET		= 0x0004,
		ENEMY				= 0x0008,
		EXPERIENCE_GLOBE	= 0x0010,

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