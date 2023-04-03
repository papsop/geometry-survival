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
	}

	// TODO
	void WeaponComponent::Update(float dt)
	{

	}

	void WeaponComponent::Fire()
	{
		if (!m_weapon)
			return;

		BulletFactoryDef def;
		def.Position = Owner.GetTransform()->GetPosition() + Owner.GetTransform()->Forward();
		def.Rotation = Owner.GetTransform()->GetRotation();
		def.Damage = m_weapon->GetBulletDamage();
		def.BulletHits = m_rpgComponent->GetStat(RPGStats::AMMO_HITS);
		def.BurningDamage = m_rpgComponent->GetStat(RPGStats::BURNING_DAMAGE);

		auto* bullet = GameObjectFactory::CreateBulletObject(def);
		Owner.GetTransform()->AddChild(bullet);
	}

	// TODO
	void WeaponComponent::Reload()
	{
	}

	// TODO
	unsigned int WeaponComponent::GetAmmo() const
	{
		return 0;
	}

	// TODO
	unsigned int WeaponComponent::GetMaxAmmo() const
	{
		return 0;
	}


}