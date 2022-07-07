#pragma once
#include "RPGStats.h"
#include "Buff/Buff.h"

#include <memory>
#include <vector>
#include <array>

namespace Game
{
	class ActorComponent;

	class RPGActor
	{
	public:
		using ptr_Buff = std::unique_ptr<Buff>;

		~RPGActor() = default;
		
		void Update(float dt);

		float GetStat(RPGStats stat);
		void  SetStatBase(RPGStats stat, float value);

		void AddBuff(ptr_Buff buff)
		{
			m_buffs.push_back(std::move(buff));
		}
	private:
		RPGActor();
		std::vector< ptr_Buff > m_buffs;

		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBase;
		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBuffBonus;
		

	friend class ActorComponent; // only ActorComponent can own a RPGActor
	};
}