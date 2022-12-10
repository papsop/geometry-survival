#include "PushdownStateMachine.h"

namespace Engine
{
	PushdownStateMachine::PushdownStateMachine()
		: m_activeState(nullptr)
		, m_states()
	{
	}

	void PushdownStateMachine::Update(float dt)
	{
		if (m_activeState)
			m_activeState->Update(dt);
	}

	bool PushdownStateMachine::IsEmpty()
	{
		return m_states.empty();
	}

	IState<PushdownStateMachine>* PushdownStateMachine::GetActiveState()
	{
		return m_activeState;
	}

	void PushdownStateMachine::ProcessMessage(const Engine::Message& message)
	{
		if (m_activeState)
			m_activeState->ProcessMessage(message);
	}

	void PushdownStateMachine::PopState()
	{
		m_activeState->OnTransitionOut();
		m_states.pop();
		m_activeState = m_states.top().get();
		m_activeState->OnTransitionIn();
	}

  void PushdownStateMachine::Clear()
  {
		while (!m_states.empty())
		{
			m_states.pop();
		}
		m_activeState = nullptr;
  }

}