#include "Actor_KnockedBack.h"
#include <Engine/Core/StateMachine/StateContainer.h>

namespace Game
{

	Actor_KnockedBack::Actor_KnockedBack(Engine::StateContainer& container, ActorComponent* actorComponent, Engine::Transform& source)
		: IState(container)
		, m_parentActor(actorComponent)
		, m_source(source)
	{

	}

	void Actor_KnockedBack::OnInit()
	{
		
	}

	void Actor_KnockedBack::OnDestroy()
	{
		
	}

	void Actor_KnockedBack::OnReset()
	{
		m_timeToRelease = 2.0f;
	}

	void Actor_KnockedBack::Update(float dt)
	{
		m_timeToRelease -= dt;
		if (m_timeToRelease < 0.0f)
			m_parentContainer.SwapCurrentAndPreviousState();
	}

	void Actor_KnockedBack::ProcessMessage(const Engine::Message& message)
	{
		
	}

}