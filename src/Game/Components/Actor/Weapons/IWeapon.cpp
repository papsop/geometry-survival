#include "IWeapon.h"
#include <Engine/Core/GameObject/GameObject.h>
#include "../WeaponComponent.h"
#include "../ActorComponent.h"
#include "../../States/Weapons.h"

namespace Game
{
	bool IWeapon::HasAmmo()
	{
		return m_currentAmmo > 0;
	}

	bool IWeapon::IsOffCooldown()
	{
		return m_currentCooldown <= 0.0f;
	}

	bool IWeapon::CanFire()
	{
		return IsOffCooldown() && HasAmmo();
	}

	void IWeapon::Reload()
	{
		m_currentAmmo = m_maxAmmo;
	}

	float IWeapon::GetWeaponCooldown()
	{
		auto finalShotsPerSecond = m_shotsPerSecond;
		auto actorAttackSpeed = m_ownerWeaponComponent.Owner.GetComponent<ActorComponent>()->GetRPGActor()->GetStat(RPGStats::ATTACK_SPEED);

		finalShotsPerSecond *= (actorAttackSpeed / 100.0f);

		return (1.0f / finalShotsPerSecond);
	}

	float IWeapon::GetWeaponDamage()
	{
		auto actorDamageModifier = m_ownerWeaponComponent.Owner.GetComponent<ActorComponent>()->GetRPGActor()->GetStat(RPGStats::WEAPON_DAMAGE);
		return m_weaponDamage * (actorDamageModifier / 100.0f);
	}

	void IWeapon::Fire()
	{
		if (CanFire())
		{
			VirtualFire();
			m_currentAmmo--;
			m_currentCooldown = GetWeaponCooldown();
			if (m_currentAmmo == 0)
			{
				m_stateMachine.AddState<Weapon_Reload>(*this, m_reloadTime);
			}
		}
	}

	void IWeapon::Update(float dt)
	{
		m_currentCooldown -= dt;
		m_stateMachine.Update(dt);
	}

	void IWeapon::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		Engine::GameObject& ownerGO = m_ownerWeaponComponent.Owner;
		Engine::math::Vec2 pos = ownerGO.GetTransform().Position + Engine::math::Vec2(0.0f, 5.0f);
		std::string ammoCount = "Ammo " + std::to_string(m_currentAmmo) + "/" + std::to_string(m_maxAmmo);
		viewStrategy->DebugRenderText(ammoCount, pos, 12.0f, sf::Color::Yellow);
	}

	void IWeapon::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MSG_Weapon_Reload && m_currentAmmo != m_maxAmmo)
		{
			m_stateMachine.AddState<Weapon_Reload>(*this, m_reloadTime);
		}

		m_stateMachine.ProcessMessage(message);
	}


};