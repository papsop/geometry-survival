#include "Weapon_Reload.h"

namespace Game
{
	template<typename T>
	Weapon_Reload<T>::Weapon_Reload(Engine::FiniteStateMachine& parentStateMachine, WeaponComponent& weaponComponent)
		: IState(parentStateMachine)
		, m_ownerWeaponComponent(weaponComponent)
	{
		m_reloadTimer = 3.0f;
		m_currentTimer = m_reloadTimer;
	}

	template<typename T>
	void Weapon_Reload<T>::OnTransitionIn()
	{
		m_currentTimer = m_reloadTimer;
	}

	template<typename T>
	void Weapon_Reload<T>::TransitionBackToT()
	{
		m_parentStateMachine.TransitionTo<T>();
	}

	template<typename T>
	void Weapon_Reload<T>::Update(float dt)
	{
		m_currentTimer -= dt;
		if (m_currentTimer <= 0.0f)
			TransitionBackToT();
	}
}