#include "RPGActor.h"
#include <Engine/Debug/Logger.h>

namespace Game
{
	RPGActor::RPGActor()
		: m_statBase()
		, m_statBuffBonus()
	{

	}

	void RPGActor::Update(float dt)
	{
	}

	void RPGActor::SetStatBase(RPGStats stat, float value)
	{
		if (stat == RPGStats::COUNT)
		{
			LOG_WARN("Trying to set RPGStats::Count");
			return;
		}

		m_statBase[static_cast<size_t>(stat)] = value;
	}

	float RPGActor::GetStat(RPGStats stat)
	{
		if (stat == RPGStats::COUNT)
		{
			LOG_WARN("Trying to retrieve RPGStats::Count, returning 0.0f");
			return 0.0f;
		}

		auto statIndex = static_cast<size_t>(stat);

		return m_statBase[statIndex] + m_statBuffBonus[statIndex];
	}



}