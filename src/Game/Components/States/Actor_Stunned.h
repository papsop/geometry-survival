#pragma once
#include <Engine/Core/StateMachine/FiniteStateMachine.h>
#include "../Actor/ActorComponent.h"

namespace Game
{

	class Actor_Stunned : public Engine::IState
	{
	public:
		Actor_Stunned(Engine::FiniteStateMachine& parentStateMachine, ActorComponent* parentActor, float duration);

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