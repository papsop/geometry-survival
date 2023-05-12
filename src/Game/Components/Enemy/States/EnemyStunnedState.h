#pragma once
#include "../EnemyComponent.h"
#include "../../Actor/RPGComponent.h"

namespace Game
{
	class EnemyStunnedState : public Engine::IState<EnemyAIStates>
	{
	public:
		EnemyStunnedState(Engine::GameObject& owner, Engine::IState<EnemyAIStates>::StateMachine& sm, float duration);
		~EnemyStunnedState() override = default;

		void Update(float dt) override;
		void OnTransitionIn() override;
		void OnTransitionOut() override;

	private:
		sf::Color m_previousColor;
		float m_duration;
	};
}