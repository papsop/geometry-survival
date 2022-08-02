#pragma once
#include <Engine/Core/StateMachine/IState.h>

namespace Game
{
	template<class T>
	class Weapon_Cooldown : public Engine::IState
	{
	public:
		Weapon_Cooldown(Engine::FiniteStateMachine& parentStateMachine, float cooldown);
		~Weapon_Cooldown() override = default;

		void OnTransitionIn() override;
		void Update(float dt) override;

	private:
		void TransitionBackToT();

		float m_cooldown;
		float m_currentCooldown;
	};
};

#include "Weapon_Cooldown.inl"