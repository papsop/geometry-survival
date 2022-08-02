#include "PistolWeapon.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Components/Physics.h>

#include "../WeaponComponent.h"
#include "../../States/Weapons/Weapon_Cooldown.h"
#include "../../States/Weapons/Weapon_Reload.h"
#include "../../States/Weapons/WeaponPistol_Shootable.h"

namespace Game
{

	PistolWeapon::PistolWeapon(WeaponComponent& weaponComponent)
		: IWeapon(weaponComponent)
	{
		m_maxAmmo = 5;
		m_currentAmmo = m_maxAmmo;

		m_stateMachine.AddState<Weapon_Cooldown<WeaponPistol_Shootable>>(0.5f);
		m_stateMachine.AddState<Weapon_Reload<WeaponPistol_Shootable>>(m_ownerWeaponComponent);
		m_stateMachine.AddState<WeaponPistol_Shootable>(m_ownerWeaponComponent);

		m_stateMachine.TransitionTo<WeaponPistol_Shootable>();
	}

}