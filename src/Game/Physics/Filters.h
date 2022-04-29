#pragma once

namespace Game
{
	namespace physics
	{
		enum EntityCategory
		{
			WALL	      = 0x0001,
			PLAYER		  = 0x0002,
			PLAYER_BULLET = 0x0004,
			ENEMY		  = 0x0008,
			ENEMY_BULLET  = 0x0010,
		};

		enum EntityMask
		{
			M_WALL			= 0xFFFF,		// collides with everything
			M_PLAYER		= EntityCategory::WALL | EntityCategory::ENEMY | EntityCategory::ENEMY_BULLET,
			M_PLAYER_BULLET	= EntityCategory::WALL | EntityCategory::ENEMY,
			M_ENEMY			= EntityCategory::WALL | EntityCategory::PLAYER | EntityCategory::PLAYER_BULLET,
			M_ENEMY_BULLET	= EntityCategory::WALL | EntityCategory::PLAYER,
		};
	}
	
}