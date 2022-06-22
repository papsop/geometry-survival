#include "Actor_KnockedBack.h"
#include "Actor_ChaseTarget.h"

namespace Game
{

	Actor_KnockedBack::Actor_KnockedBack(Engine::FiniteStateMachine& parentStateMachine, float duration)
		: IState(parentStateMachine)
		, m_knockBackDuration(duration)
		, m_knockBackTime(duration)
	{

	}

	void Actor_KnockedBack::OnTransitionIn()
	{
		m_knockBackTime = m_knockBackDuration;
	}

	void Actor_KnockedBack::Update(float dt)
	{
		m_knockBackTime -= dt;
		if (m_knockBackTime < 0.0f)
			m_parentStateMachine.TransitionTo<Actor_ChaseTarget>();
	}
}