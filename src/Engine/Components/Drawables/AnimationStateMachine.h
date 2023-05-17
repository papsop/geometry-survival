#pragma once
#include <vector>
#include <memory>

namespace Engine
{
	class AnimationClip;
	class AnimationState;
	class AnimationControllerComponent;

	// =========================================
	// Transition
	// =========================================
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

	// =========================================
	// State
	// =========================================
	class AnimationState
	{
	public:
		using TransitionsVector = std::vector<std::unique_ptr<IAnimationStateTransition>>;

		AnimationState(const char* animationName);

		bool operator==(const AnimationState& rhs)
		{
			return this->AnimationName == rhs.AnimationName;
		}

		template<typename T>
		void AddStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value);

		TransitionsVector& GetStateTransitions() { return m_transitions; };
		std::shared_ptr<AnimationClip> GetStateAnimationClip() { return m_animationClip; };
		const char* AnimationName;
	private:
		std::shared_ptr<AnimationClip> m_animationClip;
		TransitionsVector m_transitions{};
	};

	// =========================================
	// State machine
	// =========================================
	class AnimationStateMachine
	{
	public:
		AnimationStateMachine(AnimationControllerComponent& ownerController);
		~AnimationStateMachine() = default;

		void Update(float dt);
		void ResetToDefaultState();

		AnimationState* AddAnimationState(const char* animationClipName);

		template<typename T>
		void AddAnyStateTransition(AnimationState* target, const T& variable, TransitionConditionType conditionType, T value);
	private:
		AnimationControllerComponent& m_ownerController;
		std::vector<std::unique_ptr<AnimationState>> m_states;
		AnimationState* m_currentAnimationState = nullptr;
		std::vector<std::unique_ptr<IAnimationStateTransition>> m_anyStateTransitions;
		
		void CheckTransitions();
		void UpdateOwnerComponentClip();
	};
}

#include "AnimationStateMachine.inl"