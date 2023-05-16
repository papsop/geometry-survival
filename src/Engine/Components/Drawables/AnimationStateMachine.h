#pragma once
#include <vector>
#include <memory>

namespace Engine
{
	class AnimationClip;
	class AnimationState;


	class IAnimationStateTransition
	{
	public:
		IAnimationStateTransition(AnimationState* target) : TargetAnimationState(target) {};
		AnimationState* TargetAnimationState;
		virtual bool CheckTransitionCondition() = 0;
	};

	enum class TransitionConditionType
	{
		EQUALS,
		NOT_EQUALS,
		GREATER_THAN,
		// todo more?
	};

	template<typename T>
	class AnimationStateTransition : public IAnimationStateTransition
	{
	public:
		AnimationStateTransition(AnimationState* targetState, const T& variable, TransitionConditionType conditionType, T value)
			: IAnimationStateTransition(targetState)
			, VariableToCheck(variable)
			, ValueToCheck(value)
			, ConditionType(conditionType)
		{
		}
		const T& VariableToCheck;
		T	 ValueToCheck;
		TransitionConditionType ConditionType;

		bool CheckTransitionCondition() override;
	};
	

	class AnimationState
	{
	public:
		AnimationState(const char* animationName);

		template<typename T>
		void AddStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value);

		// TODO: shouldn't return a transition itself?
		IAnimationStateTransition* GetValidTransitionIfAny(); // can return null if no transitions are valid

		std::shared_ptr<AnimationClip> m_animationClip;
		std::vector<std::unique_ptr<IAnimationStateTransition>> m_transitions{};
	};

	template<typename T>
	void AnimationState::AddStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value)
	{
		AnimationStateTransition<T>* trans_ptr = new AnimationStateTransition<T>(target, variable, conditionType, value);
		auto transition = std::unique_ptr<IAnimationStateTransition>(trans_ptr);
		m_transitions.push_back(std::move(transition));
	}

}