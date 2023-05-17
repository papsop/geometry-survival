#include "AnimationStateMachine.h"
#include "../../Debug/Logger.h"
#include "../../Managers/ResourceManager.h"

namespace Engine
{
	template<>
	bool Engine::AnimationStateTransition<bool>::CheckTransitionCondition()
	{
		switch (ConditionType)
		{
		case TransitionConditionType::EQUALS:
			return VariableToCheck == ValueToCheck;
		case TransitionConditionType::NOT_EQUALS:
			return VariableToCheck != ValueToCheck;
		default:
			LOG_ERROR("ConditionType '%d' not supported for BOOLEAN transition", static_cast<int>(ConditionType));
			return false;
		}
	}

	AnimationState::AnimationState(const char* animationName)
	 : AnimationName(animationName)
	{
		m_animationClip = ResourceManager::Get().GetAnimation(animationName);
		DD_ASSERT(m_animationClip != nullptr, "Unable to find animation clip '%s'", animationName);
	}

	AnimationStateMachine::AnimationStateMachine(AnimationControllerComponent& ownerController)
		: m_ownerController(ownerController)
	{

	}

	void AnimationStateMachine::Update(float dt)
	{
		if (m_states.size() == 0)
			return;

		if (!m_currentAnimationState)
			ResetToDefaultState();

		CheckTransitions();
	}

	void AnimationStateMachine::ResetToDefaultState()
	{
		m_currentAnimationState = m_states[0].get();
		UpdateOwnerComponentClip();
	}

	AnimationState* AnimationStateMachine::AddAnimationState(const char* animationClipName)
	{
		auto state = std::make_unique<AnimationState>(animationClipName);
		m_states.emplace_back(std::move(state));
		return m_states[m_states.size() - 1].get();
	}

	void AnimationStateMachine::CheckTransitions()
	{
		bool foundValidTransition = false;
		for (const auto& transition : m_currentAnimationState->GetStateTransitions())
		{
			if (transition->CheckTransitionCondition())
			{
				m_currentAnimationState = transition->TargetAnimationState;
				foundValidTransition = true;
				UpdateOwnerComponentClip();
				break;
			}
		}

		if (!foundValidTransition)
		{
			for (const auto& transition : m_anyStateTransitions)
			{
				if(transition->TargetAnimationState == m_currentAnimationState)
					continue;

				if (transition->CheckTransitionCondition())
				{
					m_currentAnimationState = transition->TargetAnimationState;
					UpdateOwnerComponentClip();
					break;
				}
			}
		}
	}

	void AnimationStateMachine::UpdateOwnerComponentClip()
	{
		m_ownerController.PlayAnimationClipFromSM(m_currentAnimationState->AnimationName);
	}

}