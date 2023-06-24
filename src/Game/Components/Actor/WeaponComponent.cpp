#include "WeaponComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include "../../Core/GameObject/GameObjectFactory.h"

#include "Weapons.h"

namespace Game
{
	WeaponComponent::WeaponComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_bulletHandler(*this)
	{
		SetRequiredComponents<RPGComponent>();
	}

	void WeaponComponent::VirtualOnCreate()
	{
		m_rpgComponent = Owner.GetComponent<RPGComponent>();
	}

	void WeaponComponent::VirtualOnActivated()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
		Engine::IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void WeaponComponent::VirtualOnDeactivated()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
		Engine::IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

	void WeaponComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
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

		Engine::math::Vec2 dir = (m_targetPosition - Owner.GetTransform()->GetPosition());
		dir.Normalize();
    float angle = Engine::math::AngleOfVec(dir);

		BulletFactoryDef def;
		def.Position = Owner.GetTransform()->GetPosition() + dir;
		def.Rotation = angle;
		def.Damage = m_weapon->GetBulletDamage() + m_rpgComponent->GetStat(RPGStats::WEAPON_DAMAGE);
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