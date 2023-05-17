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

}