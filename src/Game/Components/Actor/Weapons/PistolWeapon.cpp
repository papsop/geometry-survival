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
		m_maxAmmo = 5;
		m_currentAmmo = m_maxAmmo;
		m_shootingCooldown = 0.2f;

		m_stateMachine.AddState<WeaponPistol_Shootable>(*this);
	}

	void PistolWeapon::VirtualFire()
	{
		auto& ownerGO = m_ownerWeaponComponent.Owner;
		auto* bullet = m_ownerWeaponComponent.CreateBulletGameObject();
		auto forward = ownerGO.GetTransform().Forward();
		forward *= 30.0f;
		bullet->GetComponent<Engine::PhysicsBodyComponent>()->ApplyImpulseToCenter(forward);
	}

}