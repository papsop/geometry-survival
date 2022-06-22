#pragma once
#include "../../Utils/IdGenerator.h"
#include "IState.h"

#include <unordered_map>
#include <memory>

namespace Engine
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine() = default;
		~FiniteStateMachine() = default;

		template<typename T>
		void TransitionTo();

		template
		<
			typename T,
			typename ... Args,
			typename = enable_if_base_of_state<T>
		>
		void AddState(Args&&... args);

		template
		<
			typename T,
			typename = enable_if_base_of_state<T>
		>
		bool HasState();


		void Update(float dt);

	private:
		std::unordered_map< size_t, std::unique_ptr<IState> > m_states;
		IState* m_activeState = nullptr;
		//size_t m_previousStateId;
	};
};

#include "FiniteStateMachine.inl"