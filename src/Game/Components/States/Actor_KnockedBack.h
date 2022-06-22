#pragma once
#include <Engine/Core/StateMachine/FiniteStateMachine.h>

namespace Game
{

	class Actor_KnockedBack : public Engine::IState
	{
	public:
		Actor_KnockedBack(Engine::FiniteStateMachine& parentStateMachine, float duration);

		void OnTransitionIn() override;
		void Update(float dt) override;

	private:
		float m_knockBackDuration;
		float m_knockBackTime;
	};

}