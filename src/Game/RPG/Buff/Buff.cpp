#include "Buff.h"
#include <Engine/Debug/Logger.h>

namespace Game
{
	Buff::Buff(float duration)
		: m_timer(duration)
		, m_shouldDestroy(false)
	{
		// negative number when creating -> infinite duration
		m_isTimed = (m_timer < 0.0f) ? false : true;
	}

	void Buff::Update(float dt)
	{
		if (m_isTimed)
		{
			m_timer -= dt;
			if (m_timer <= 0.0f)
				m_shouldDestroy = true;
		}
			

		if (!m_shouldDestroy)
		{
			VirtualUpdate(dt);
		}
		LOG_WARN("Updating buff");
	}

	Buff& Buff::AddModifier(RPGStats stat, float value)
	{
		m_buffModifiers.push_back({stat, value});
		return *this;
	}

	void Buff::IterateOverModifiers(IterateFunction func)
	{
		for (auto&& modifier : m_buffModifiers)
		{
			func(modifier);
		}
	}

}