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
		AMMO_HITS, // pierces

		COUNT // always last
	};
};