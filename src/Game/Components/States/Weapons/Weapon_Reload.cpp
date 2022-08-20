#include "Weapon_Reload.h"

namespace Game
{
	Weapon_Reload::Weapon_Reload(Engine::PushdownStateMachine& stateMachine, IWeapon& weapon, float reloadTime)
		: IState(stateMachine)
		, m_reloadTime(reloadTime)
		, m_ownerWeapon(weapon)
	{
	}

	void Weapon_Reload::OnTransitionIn()
	{
		m_ownerWeapon.SetWeaponState(IWeapon::WeaponState::Reloading);
	}

	void Weapon_Reload::Update(float dt)
	{
		m_reloadTime -= dt;
		if (m_reloadTime <= 0.0f)
		{
			m_ownerWeapon.Reload();
			m_parentStateMachine.PopState(); // go back to shooting
		}
	}
};