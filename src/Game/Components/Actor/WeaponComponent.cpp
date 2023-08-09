#include "WeaponComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include "../../Core/GameObject/GameObjectFactory.h"
#include "BulletComponent.h"
#include "Weapons.h"

namespace Game
{
	WeaponComponent::WeaponComponent(Engine::GameObject& obj)
		: IComponent(obj)
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

	void WeaponComponent::RegisterBulletMiddleware(IBulletMiddleware* middleware)
	{
		m_middlewares.push_back(middleware);
	}

	void WeaponComponent::UnregisterBulletMiddleware(IBulletMiddleware* middleware)
	{
		m_middlewares.erase(std::remove(m_middlewares.begin(), m_middlewares.end(), middleware), m_middlewares.end());
	}

	void WeaponComponent::EquipWeapon(std::unique_ptr<WeaponData> weapon)
	{
		m_weapon = std::move(weapon);
	}
  bool WeaponComponent::IsOnCooldown() const
  {
		return m_cooldown > 0.0f;
  }

	void WeaponComponent::Update(float dt)
	{
		if (IsOnCooldown())
		{
			m_cooldown -= dt;
		}
	}

	void WeaponComponent::Fire()
	{
		if (!m_weapon)
			return;

		if (IsOnCooldown())
			return;

		Engine::math::Vec2 dir = (m_targetPosition - Owner.GetTransform()->GetPosition());
		dir.Normalize();
    float angle = Engine::math::AngleOfVec(dir);

		BulletFactoryDef def;
		def.Position = Owner.GetTransform()->GetPosition() + dir;
		def.Rotation = angle;
		//def.Damage = m_weapon->GetBulletDamage() + m_rpgComponent->GetStat(RPGStats::WEAPON_DAMAGE);
		//def.BulletHits = m_rpgComponent->GetStat(RPGStats::AMMO_HITS);
		//def.BurningDamage = m_rpgComponent->GetStat(RPGStats::BURNING_DAMAGE);

		auto* bullet = GameObjectFactory::CreateBulletObject(def);

		for (auto* middleware : m_middlewares)
		{
			middleware->Middleware(*bullet);
		}

		Owner.GetTransform()->AddChild(bullet);

		m_cooldown = m_weapon->GetFireRate();
	}
}