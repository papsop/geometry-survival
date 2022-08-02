#include "IWeapon.h"
#include <Engine/Core/GameObject/GameObject.h>
#include "../WeaponComponent.h"

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



	void IWeapon::Update(float dt)
	{
		m_currentShootingCooldown -= dt;
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
		m_stateMachine.ProcessMessage(message);
	}

	void IWeapon::Reload()
	{
		Engine::Message message;
		message.Sender = &m_ownerWeaponComponent.Owner;
		message.Type = Engine::MessageType::MSG_Weapon_Reload;
		ProcessMessage(message);
	}

	void IWeapon::RefillAmmo()
	{
		m_currentAmmo = m_maxAmmo;
	}

	void IWeapon::Fire()
	{
		Engine::Message message;
		message.Sender = &m_ownerWeaponComponent.Owner;
		message.Type = Engine::MessageType::MSG_Weapon_Fire;
		ProcessMessage(message);
	}

};