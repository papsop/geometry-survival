#include "StateContainer.h"

namespace Engine
{

	void StateContainer::Update(float dt)
	{
		for (auto& globalState : m_globalStates)
			globalState->Update(dt);

		if (m_currentState)
			m_currentState->Update(dt);
	}

	void StateContainer::SwapCurrentAndPreviousState()
	{
		std::swap(m_currentState, m_previousState);
		m_currentState->OnReset();
	}

	void StateContainer::ProcessMessage(const Message& message)
	{
		for (auto& globalState : m_globalStates)
			globalState->ProcessMessage(message);

		if (m_currentState)
			m_currentState->ProcessMessage(message);
	}

}