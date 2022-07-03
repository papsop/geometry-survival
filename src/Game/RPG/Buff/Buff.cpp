#include "Buff.h"
#include <Engine/Debug/Logger.h>

namespace Game
{
	Buff::Buff()
		: m_timer(-1.0f)
		, m_shouldDestroy(false)
	{
		m_isInfinite = (m_timer == -1.0f) ? true : false;
	}

	void Buff::Update(float dt)
	{
		if (m_isInfinite)
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
}