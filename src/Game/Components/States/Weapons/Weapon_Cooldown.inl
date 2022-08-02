#include "Weapon_Cooldown.h"

namespace Game
{
	template<typename T>
	Weapon_Cooldown<T>::Weapon_Cooldown(Engine::FiniteStateMachine& parentStateMachine, float cooldown)
		: IState(parentStateMachine)
	{
		m_currentCooldown = cooldown;
		m_cooldown = cooldown;
	}

	template<typename T>
	void Weapon_Cooldown<T>::OnTransitionIn()
	{
		m_currentCooldown = m_cooldown;
	}

	template<typename T>
	void Weapon_Cooldown<T>::TransitionBackToT()
	{
		m_parentStateMachine.TransitionTo<T>();
	}

	template<typename T>
	void Weapon_Cooldown<T>::Update(float dt)
	{
		m_currentCooldown -= dt;
		if (m_currentCooldown <= 0.0f)
			TransitionBackToT();
	}
}