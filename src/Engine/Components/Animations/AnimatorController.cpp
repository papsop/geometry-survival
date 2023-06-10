#include "AnimatorController.h"
#include "AnimatorComponent.h"

#include "../../Debug/Logger.h"
namespace Engine
{

	// ====================================================
	// State transition
	// ====================================================

	template<>
	bool AnimatorStateTransition<bool>::CheckTransitionCondition() const
	{
		switch (m_conditionType)
		{
		case AnimatorTransitionConditionType::EQUALS:
			return m_variable == m_value;
		case AnimatorTransitionConditionType::NOT_EQUALS:
			return m_variable == m_value;
		default:
			LOG_ERROR("ConditionType '%d' not supported for BOOLEAN transition", static_cast<int>(m_conditionType));
			return false;
		}
	}

	// ====================================================
	// State
	// ====================================================

	AnimatorState::AnimatorState(AnimatorController& controller, const char* clip, bool isLooped)
		: m_ownerController(controller)
		, m_animationData()
	{
		m_animationData.Clip = clip;
		m_animationData.IsLooped = isLooped;
	}

	const AnimatorState::T_AnimatorStateTransitions& AnimatorState::GetStateTransitions()
	{
		return m_transitions;
	}

	AnimationPlayData AnimatorState::GetAnimationPlayData()
	{
		return m_animationData;
	}

	void AnimatorState::OnStateEntering()
	{
		LOG_INFO("Entering animation state '%s'", m_animationData.Clip);
		// TODO: not needed right now, maybe add something later
	}

	void AnimatorState::OnStateLeaving()
	{
		LOG_INFO("Leaving animation state '%s'", m_animationData.Clip);
		// TODO: not needed right now, maybe add something later
	}

	void AnimatorState::OnAnimationStarted()
	{
		OnAnimationStartedSignal.Invoke();
	}

	void AnimatorState::OnAnimationFinished()
	{
		OnAnimationFinishedSignal.Invoke();
	}

	// ====================================================
	// Controller
	// ====================================================

	AnimatorState* AnimatorController::AddAnimatorState(const char* clip, bool isLooped)
	{
		auto state = std::make_unique<AnimatorState>(*this, clip, isLooped);
		AnimatorState* ptr_state = state.get();
		m_states.push_back(std::move(state));

		// First added state should be the default one
		if (m_states.size() == 1 && !m_defaultState)
		{
			m_defaultState = ptr_state;
		}

		return ptr_state;
	}

	void AnimatorController::SetDefaultState(AnimatorState* state)
	{
		m_defaultState = state;
	}

	void AnimatorController::Update(float dt)
	{
		if (m_states.size() == 0)
			return; // wasting an update

		if (!m_currentState && m_defaultState)
		{
			TransitionIntoState(m_defaultState);
		}

		for (const auto& transition : m_currentState->GetStateTransitions())
		{
			if (transition->CheckTransitionCondition())
			{
				TransitionIntoState(transition->GetTargetState());
			}
		}

	}

	void AnimatorController::SetOwnerAnimatorComponent(AnimatorComponent* owner)
	{
		m_ownerComponent = owner;
	}

	void AnimatorController::TransitionIntoState(AnimatorState* state)
	{
		if (m_currentState)
		{
			m_currentState->OnStateLeaving();
		}

		m_currentState = state;

		m_currentState->OnStateEntering();

		if (m_ownerComponent)
		{
			AnimationPlayData playData = m_currentState->GetAnimationPlayData();
			AnimationPlayRequest request;
			request.Data = playData;
			request.Requester = this;

			m_ownerComponent->RequestAnimationPlay(request);
		}
	}

}