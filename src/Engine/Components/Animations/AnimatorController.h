#pragma once
#include "AnimationData.h"
#include "../../Core/Signal.h"

#include <memory>
#include <vector>

namespace Engine
{

	class AnimatorState;
	class AnimatorController;
	class AnimatorComponent;

	// ====================================================
	// State transition
	// ====================================================

	enum class AnimatorTransitionConditionType
	{
		EQUALS,
		NOT_EQUALS,
		GREATER_THAN,
		// ... add more later if needed
	};

	class IAnimatorStateTransition
	{
	public:
		virtual ~IAnimatorStateTransition() = default;
		virtual bool CheckTransitionCondition() const = 0;
		virtual AnimatorState* GetTargetState() const = 0;
	};

	template<typename T>
	class AnimatorStateTransition final : public IAnimatorStateTransition
	{
	public:
		AnimatorStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value);
		~AnimatorStateTransition() override = default;

		virtual bool CheckTransitionCondition() const;
		virtual AnimatorState* GetTargetState() const;
	private:
		AnimatorState* m_target;
		const T& m_variable;
		AnimatorTransitionConditionType m_conditionType;
		T m_value;
	};

	// ====================================================
	// State
	// ====================================================

	struct AnimatorStateAnimationData
	{
		const char* AnimationClip;
		bool IsLooped;
		// maybe todo more
	};

	class AnimatorState
	{
	public:		
		friend class AnimatorController;

		using T_AnimatorStateTransitions = std::vector< std::unique_ptr<IAnimatorStateTransition> >;
		AnimatorState(AnimatorController& controller, const char* clip, bool isLooped);

		template<typename T>
		void AddStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value);
		const T_AnimatorStateTransitions& GetStateTransitions();

		AnimationPlayData GetAnimationPlayData();

		Signal<void> OnAnimationStartedSignal;
		Signal<void> OnAnimationFinishedSignal;

		// Do we need loop animation signals?
		//Signal<void> OnAnimationLoopFinishedSignal;
		//Signal<void> OnAnimationLoopStartedSignal;

	protected:
		void OnStateEntering();
		void OnStateLeaving();

		void OnAnimationStarted();
		void OnAnimationFinished();

	private:
		AnimatorController& m_ownerController;
		AnimationPlayData m_animationData;
		T_AnimatorStateTransitions m_transitions;
	};

	// ====================================================
	// Controller
	// ====================================================

	class AnimatorController final : public IAnimationPlayRequester
	{
	public:
		friend class AnimatorComponent;

		AnimatorController() = default;
		~AnimatorController() = default;

		AnimatorState* AddAnimatorState(const char* clip, bool isLooped);

		template<typename T>
		void AddAnyStateTransition(AnimatorState* target, const T& variable, AnimatorTransitionConditionType condType, T value);

		void SetDefaultState(AnimatorState* state);

		void Update(float dt);

	protected:
		void SetOwnerAnimatorComponent(AnimatorComponent* owner);
		void OnAnimationStarted() override;
		void OnAnimationFinished() override;

	private:
		AnimatorComponent* m_ownerComponent = nullptr;
		std::vector< std::unique_ptr<AnimatorState> > m_states;
		AnimatorState::T_AnimatorStateTransitions m_anyTransitions;

		AnimatorState* m_defaultState = nullptr;
		AnimatorState* m_currentState = nullptr;

		void TransitionIntoState(AnimatorState* state);

	};

}

#include "AnimatorController.inl"