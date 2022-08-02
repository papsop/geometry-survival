#include "FiniteStateMachine.h"
#include "../../Debug/Logger.h"
#include "../../Utils/IdGenerator.h"

namespace Engine
{
	template<typename T>
	void FiniteStateMachine::TransitionTo()
	{
		if (HasState<T>())
		{
			auto idOfT = IdGenerator<FiniteStateMachine>::GetID<T>();

			if (m_activeState)
				m_activeState->OnTransitionOut();

			m_activeState = m_states[idOfT].get();
			m_activeState->OnTransitionIn();
		}
		else
			LOG_WARN("Trying to transition into state that's not present '%s'", typeid(T).name());
	}

	template<typename T>
	void FiniteStateMachine::TransitionTo(T* state)
	{
		TransitionTo<T>();
	}

	template<typename T, typename ... Args, typename>
	void FiniteStateMachine::AddState(Args&&... args)
	{
		if (!HasState<T>())
		{
			auto idOfT = IdGenerator<FiniteStateMachine>::GetID<T>();
			m_states[idOfT] = std::make_unique<T>(*this, std::forward<Args>(args)...);
		}
		else
			LOG_WARN("State '%s' already present", typeid(T).name());
	}

	template<typename T, typename>
	bool FiniteStateMachine::HasState()
	{
		auto idOfT = IdGenerator<FiniteStateMachine>::GetID<T>();
		return (m_states.find(idOfT) != m_states.end());
	}
};