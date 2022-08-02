#include "FiniteStateMachine.h"

namespace Engine
{

	void FiniteStateMachine::Update(float dt)
	{
		if (m_activeState)
			m_activeState->Update(dt);
	}

	void FiniteStateMachine::ProcessMessage(const Engine::Message& message)
	{
		m_activeState->ProcessMessage(message);
	}

}