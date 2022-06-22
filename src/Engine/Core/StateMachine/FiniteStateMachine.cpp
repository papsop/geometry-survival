#include "FiniteStateMachine.h"

namespace Engine
{
	void FiniteStateMachine::Update(float dt)
	{
		if (m_activeState)
			m_activeState->Update(dt);
	}
}