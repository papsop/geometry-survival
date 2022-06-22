#pragma once
#include <memory>
#include <vector>

#include "IState.h"
#include "../Messaging/MessageTypes.h"

namespace Engine
{
	class StateContainer
	{
	public:
		void Update(float dt);


		template<typename T,
				typename ... Args,
				typename = enable_if_base_of_state<T>
				>
		void CreateAndSetState(Args&& ... args);

		void SwapCurrentAndPreviousState();
		void ProcessMessage(const Message& message);

	private:
		std::unique_ptr<IState> m_currentState;
		std::unique_ptr<IState> m_previousState;
		std::vector< std::unique_ptr<IState> > m_globalStates;
	};
}

#include "StateContainer.inl"