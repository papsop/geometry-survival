#include "WeaponComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{
	WeaponComponent::WeaponComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<RPGComponent>();
	}

	void WeaponComponent::OnCreate()
	{
		m_rpgComponent = Owner.GetComponent<RPGComponent>();
	}

	void WeaponComponent::VirtualOnActivated()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	void WeaponComponent::VirtualOnDeactivated()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void WeaponComponent::EquipWeapon(std::unique_ptr<WeaponData> weapon)
	{
		m_weapon = std::move(weapon);
		m_ammo = m_weapon->GetMaxAmmo();
	}

  unsigned int WeaponComponent::GetAmmo() const
  {
    return m_ammo;
  }

  unsigned int WeaponComponent::GetMaxAmmo() const
  {
    return (m_weapon) ? m_weapon->GetMaxAmmo() : 0;
  }

  bool WeaponComponent::IsOnCooldown() const
  {
		return m_cooldown > 0.0f;
  }

  bool WeaponComponent::HasAmmo() const
  {
		return GetAmmo() > 0;
  }

  float WeaponComponent::GetReloadTimer() const
  {
    return m_reloadTimer;
  }

  float WeaponComponent::GetReloadCompletion() const
  {
    if (!m_weapon)
      return 0.0f;

		return (m_weapon->GetReloadTime() - GetReloadTimer()) / m_weapon->GetReloadTime();
  }

  bool WeaponComponent::IsReloading() const
  {
		return GetReloadTimer() > 0.0f;
  }

  bool WeaponComponent::IsFireable() const
  {
		return HasAmmo() && !IsOnCooldown() && !IsReloading();
  }

  void WeaponComponent::Update(float dt)
	{
		if (m_reloadTimer > 0.0f)
		{
			m_reloadTimer -= dt;

			if (m_reloadTimer <= 0.0f)
				FinishReload();
		}

		if (IsOnCooldown())
		{
			m_cooldown -= dt;
		}
	}

	void WeaponComponent::Fire()
	{
		if (!m_weapon)
			return;

		if (!IsFireable())
			return;

		BulletFactoryDef def;
		def.Position = Owner.GetTransform()->GetPosition() + Owner.GetTransform()->Forward();
		def.Rotation = Owner.GetTransform()->GetRotation();
		def.Damage = m_weapon->GetBulletDamage();
		def.BulletHits = m_rpgComponent->GetStat(RPGStats::AMMO_HITS);
		def.BurningDamage = m_rpgComponent->GetStat(RPGStats::BURNING_DAMAGE);

		auto* bullet = GameObjectFactory::CreateBulletObject(def);
		Owner.GetTransform()->AddChild(bullet);

		m_ammo--;
		m_cooldown = m_weapon->GetFireRate();

		if (m_ammo == 0)
		{
			InitiateTimedReload();
		}
	}

  void WeaponComponent::InitiateTimedReload()
  {
    if (!m_weapon)
      return;

		if (m_reloadTimer > 0.0f)
			return;

    m_reloadTimer = m_weapon->GetReloadTime();
  }

  void WeaponComponent::FinishReload()
  {
    if (!m_weapon)
      return;

		m_reloadTimer = 0.0f;
		m_ammo = m_weapon->GetMaxAmmo();
  }

}