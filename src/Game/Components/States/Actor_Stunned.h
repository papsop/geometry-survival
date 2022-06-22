#pragma once
#include <Engine/Core/StateMachine/FiniteStateMachine.h>

namespace Game
{

	class Actor_Stunned : public Engine::IState
	{
	public:
		Actor_Stunned(Engine::FiniteStateMachine& parentStateMachine, float duration);

		void OnTransitionIn() override;
		void Update(float dt) override;

	private:
		float m_stunDuration;
		float m_stunTime;
	};

}