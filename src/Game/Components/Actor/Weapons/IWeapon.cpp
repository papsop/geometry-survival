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
		m_currentAmmo = GetWeaponMaxAmmo();
	}

	float IWeapon::GetWeaponCooldown()
	{
		auto finalShotsPerSecond = m_shotsPerSecond;
		auto actorAttackSpeed = m_ownerWeaponComponent.Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::ATTACK_SPEED);

		finalShotsPerSecond *= (actorAttackSpeed / 100.0f);

		return (1.0f / finalShotsPerSecond);
	}

	float IWeapon::GetWeaponDamage()
	{
		auto actorDamageModifier = m_ownerWeaponComponent.Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::WEAPON_DAMAGE);
		return m_weaponDamage * (actorDamageModifier / 100.0f);
	}

	int IWeapon::GetWeaponMaxAmmo()
	{
		auto maxAmmoModifier = m_ownerWeaponComponent.Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::AMMO_BONUS);
		return std::ceil(m_maxAmmo * (maxAmmoModifier / 100.0f));
	}

	int IWeapon::GetCurrentAmmoCount()
	{
		return m_currentAmmo;
	}

	void IWeapon::SetWeaponState(WeaponState state)
	{
		m_currentWeaponState = state;
	}

	void IWeapon::Fire()
	{
		if (CanFire())
		{
			VirtualFire();
			m_currentAmmo--;
			m_currentCooldown = GetWeaponCooldown();
			auto rpgActor = m_ownerWeaponComponent.Owner.GetComponent<RPGComponent>();

			auto buff = std::make_unique<Buff>(GetWeaponCooldown(), Buff::BuffTag::MovementSlowAfterShooting);
			buff->AddPercentageModifier(RPGStats::MOVEMENT_SPEED, -0.5f);

			rpgActor->AddBuff(std::move(buff));

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
		Engine::math::Vec2 pos = ownerGO.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, 5.0f);
		std::string ammoCount = "Ammo " + std::to_string(m_currentAmmo) + "/" + std::to_string(GetWeaponMaxAmmo());
		viewStrategy->DebugRenderText(Engine::ITransform::PositionSpace::WorldSpace, ammoCount, pos, 12.0f, sf::Color::Yellow);
	}

	void IWeapon::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MessageType::Weapon_Reload
			&& m_currentAmmo != m_maxAmmo
			&& m_currentWeaponState != WeaponState::Reloading)
		{
			m_stateMachine.AddState<Weapon_Reload>(*this, m_reloadTime);
		}
		m_stateMachine.ProcessMessage(message);
	}


};