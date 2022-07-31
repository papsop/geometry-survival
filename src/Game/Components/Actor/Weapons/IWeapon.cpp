#include "IWeapon.h"

namespace Game
{
	bool IWeapon::HasAmmo()
	{
		return m_currentAmmo > 0;
	}

	bool IWeapon::IsOffCooldown()
	{
		return m_currentShootingCooldown <= 0.0f;
	}

	bool IWeapon::CanFire()
	{
		return IsOffCooldown() && HasAmmo();
	}

	void IWeapon::Reload()
	{
		// TODO an actual reloading state
		m_currentAmmo = m_maxAmmo;
	}

	void IWeapon::Update(float dt)
	{
		m_currentShootingCooldown -= dt;
	}

	void IWeapon::Fire()
	{
		if (CanFire())
		{
			VirtualFire();
			--m_currentAmmo;
			m_currentShootingCooldown = m_shootingCooldown;
		}
	}

};