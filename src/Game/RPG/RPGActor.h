#pragma once
#include "RPGStats.h"
#include "Buff/Buff.h"

#include <memory>
#include <vector>
#include <array>

namespace Game
{
	class ActorComponent;
	
	struct RPGActorDef
	{
		unsigned int MaxHealth;
		// meters per seconds
		float MovementSpeed;
		// shots per second = weapon * (attack speed/100)
		float AttackSpeed = 100.0f;
		// damage = weapon * (damage/100)
		float WeaponDamage = 100.0f;
		// ammmo = ceil(weapon * (bonus/100)) 
		float AmmoBonus = 100.0f;
	};

	class RPGActor
	{
	public:
		using ptr_Buff = std::unique_ptr<Buff>;

		~RPGActor() = default;
		
		void Update(float dt);

		float GetStat(RPGStats stat);
		void  SetStatBase(RPGStats stat, float value);

		void AddBuff(ptr_Buff buff);
	private:
		RPGActor(const RPGActorDef& rpgActorDef);
		std::vector< ptr_Buff > m_buffs;

		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBase;
		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBuffBonus;
		

	friend class ActorComponent; // only ActorComponent can own a RPGActor
	};
}