#include "PushdownStateMachine.h"

namespace Engine
{
	template<typename T, typename ... Args, typename>
	void PushdownStateMachine::AddState(Args&& ... args)
	{
		if(m_activeState)
			m_activeState->OnTransitionOut();
		m_states.push(std::make_unique<T>(*this, std::forward<Args>(args) ...));
		m_activeState = m_states.top().get();
		m_activeState->OnTransitionIn();
	}
};