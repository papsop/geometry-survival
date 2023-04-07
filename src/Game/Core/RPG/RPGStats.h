#pragma once

namespace Game
{
	enum class RPGStats
	{
		MAX_HEALTH,
		CURRENT_HEALTH,
		MOVEMENT_SPEED,
		ATTACK_SPEED,
		WEAPON_DAMAGE,
		AMMO_BONUS,
		AMMO_ON_KILL,
		AMMO_HITS, // number of bullet pierces
		PICKUP_FIELD_SIZE,
		BURNING_DAMAGE, // damage per tick, applies to bullets
		FROZEN,
		SCATTER_TARGETS,

		COUNT // always last
	};
};