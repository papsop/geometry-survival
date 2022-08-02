#pragma once
#include "IState.h"
#include <stack>
#include <memory>

namespace Engine
{
	class PushdownStateMachine
	{
	public:
		using PushdownState = IState<PushdownStateMachine>;

		PushdownStateMachine();
		~PushdownStateMachine() = default;

		void Update(float dt);
		void PopState();

		template<typename T,
				typename ... Args,
			typename = enable_if_base_of_state<PushdownStateMachine, T>
		>
		void AddState(Args&& ... args);

		bool IsEmpty();
		PushdownState* GetActiveState();

		void ProcessMessage(const Engine::Message& message);
	private:
		std::stack< std::unique_ptr<PushdownState> > m_states;
		PushdownState* m_activeState;
	};
};

#include "PushdownStateMachine.inl"