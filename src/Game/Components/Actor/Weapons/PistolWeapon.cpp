#include "PistolWeapon.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Components/Physics.h>


#include "../WeaponComponent.h"
#include "../../States/Weapons.h"

namespace Game
{

	PistolWeapon::PistolWeapon(WeaponComponent& weaponComponent)
		: IWeapon(weaponComponent)
	{
		m_currentAmmo = m_maxAmmo = 10;
		m_reloadTime = 1.0f;

		m_shotsPerSecond = 3.2f;
		m_weaponDamage = 5.0f;
		
		m_stateMachine.AddState<WeaponPistol_Shootable>(*this);
	}

	void PistolWeapon::VirtualFire()
	{
		m_ownerWeaponComponent.CreateBulletGameObject();
	}

}