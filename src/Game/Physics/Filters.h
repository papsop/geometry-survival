#pragma once

namespace Game
{
	namespace physics
	{
		enum EntityCategory : uint16
		{
			WALL									= 0x0001,
			PLAYER								= 0x0002,
			PLAYER_BULLET					= 0x0004,
			PLAYER_BULLET_FIELD		= 0x0008,
			ENEMY									= 0x0010,
			ENEMY_BULLET					= 0x0020,
			PICKUP_FIELD					= 0x0040,
			PICKABLE							= 0x0080,
		};

		enum EntityMask : uint16
		{
			M_WALL								= 0xFFFF,		// collides with everything
			M_PLAYER							= EntityCategory::WALL | EntityCategory::ENEMY | EntityCategory::ENEMY_BULLET | EntityCategory::PLAYER,
			M_PLAYER_BULLET				= EntityCategory::WALL | EntityCategory::ENEMY,
			M_PLAYER_BULLET_FIELD	= EntityCategory::ENEMY,
			M_ENEMY								= EntityCategory::WALL | EntityCategory::PLAYER | EntityCategory::PLAYER_BULLET | EntityCategory::ENEMY | EntityCategory::PLAYER_BULLET_FIELD,
			M_ENEMY_BULLET				= EntityCategory::WALL | EntityCategory::PLAYER,
			M_PICKABLE						= EntityCategory::PICKUP_FIELD | EntityCategory::PLAYER,
			M_PICKUP_FIELD				= EntityCategory::PICKABLE
		};
	}
	
}