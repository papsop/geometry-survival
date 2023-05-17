#include "AnimationStateMachine.h"

namespace Engine
{
	template<typename T>
	void AnimationState::AddStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value)
	{
		AnimationStateTransition<T>* trans_ptr = new AnimationStateTransition<T>(target, variable, conditionType, value);
		auto transition = std::unique_ptr<IAnimationStateTransition>(trans_ptr);
		m_transitions.push_back(std::move(transition));
	}

	template<typename T>
	void AnimationStateMachine::AddAnyStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value)
	{
		AnimationStateTransition<T>* trans_ptr = new AnimationStateTransition<T>(target, variable, conditionType, value);
		auto transition = std::unique_ptr<IAnimationStateTransition>(trans_ptr);
		m_anyStateTransitions.push_back(std::move(transition));
	}
}