#include "AnimatorController.h"

namespace Engine
{

	// ====================================================
	// State transition
	// ====================================================

	template<typename T>
	AnimatorStateTransition<T>::AnimatorStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value)
		: m_target(target)
		, m_variable(variable)
		, m_conditionType(condType)
		, m_value(value)
	{

	}

	template<typename T>
	AnimatorState* AnimatorStateTransition<T>::GetTargetState() const
	{
		return m_target;
	}

	// ====================================================
	// State
	// ====================================================

	template<typename T>
	void AnimatorState::AddStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value)
	{
		DD_ASSERT(target != nullptr, "Trying to add a null state transition");
		std::unique_ptr<IAnimatorStateTransition> transition = std::make_unique<AnimatorStateTransition<T>>(target, variable, condType, value);
		m_transitions.push_back(std::move(transition));
	}

	// ====================================================
	// Controller
	// ====================================================
	template<typename T>
	void AnimatorController::AddAnyStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value)
	{
		DD_ASSERT(target != nullptr, "Trying to add a null state transition");
		std::unique_ptr<IAnimatorStateTransition> transition = std::make_unique<AnimatorStateTransition<T>>(target, variable, condType, value);
		m_anyTransitions.push_back(std::move(transition));
	}
}