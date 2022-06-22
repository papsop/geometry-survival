#include "Actor_KnockedBack.h"
#include "Actor_ChaseTarget.h"

namespace Game
{

	Actor_Stunned::Actor_Stunned(Engine::FiniteStateMachine& parentStateMachine, float duration)
		: IState(parentStateMachine)
		, m_stunDuration(duration)
		, m_stunTime(duration)
	{

	}

	void Actor_Stunned::OnTransitionIn()
	{
		m_stunTime = m_stunDuration;
	}

	void Actor_Stunned::Update(float dt)
	{
		m_stunTime -= dt;
		if (m_stunTime < 0.0f)
			m_parentStateMachine.TransitionTo<Actor_ChaseTarget>();
	}
}