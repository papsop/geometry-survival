#pragma once
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Actor/ActorComponent.h"

namespace Game
{
	class Actor_Stunned : public Engine::IState<Engine::PushdownStateMachine>
	{
	public:
		Actor_Stunned(Engine::PushdownStateMachine& parentStateMachine, ActorComponent* parentActor, float duration);

		void OnTransitionIn() override;
		void OnTransitionOut() override;

		void Update(float dt) override;

	private:
		ActorComponent* m_parentActor;
		Engine::ShapeViewComponent* m_shapeViewComponent;
		sf::Color m_previousColor;

		float m_stunDuration;
		float m_stunTime;
	};

}