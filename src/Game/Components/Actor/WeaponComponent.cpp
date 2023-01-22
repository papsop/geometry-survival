#include "WeaponComponent.h"
#include "ActorComponent.h"
#include "BulletComponent.h"

#include "../Player/PlayerComponent.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/GameObject/GameObjectTag.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/ViewManager.h>
#include <Engine/Managers/InputManager.h>
#include <Engine/Components/Physics.h>


#include "../../Physics/Filters.h"
namespace Game
{
  WeaponComponent::WeaponComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
    SetRequiredComponents<ActorComponent>();
  }

  void WeaponComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
    m_rpgComponent = Owner.GetComponent<RPGComponent>();
  }

  WeaponComponent::~WeaponComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void WeaponComponent::VirtualOnActivated()
  {
    Engine::IEventListener<event::E_EnemyDied>::RegisterListener();
  }

  void WeaponComponent::VirtualOnDeactivated()
  {
    Engine::IEventListener<event::E_EnemyDied>::UnregisterListener();
  }


  void WeaponComponent::Update(float dt)
  {
    if (m_equippedWeapon)
      m_equippedWeapon->Update(dt);
  }

  void WeaponComponent::EquipWeapon(std::unique_ptr<IWeapon> weapon)
  {
    m_equippedWeapon = std::move(weapon);
  }

  void WeaponComponent::Fire()
  {
    if (m_equippedWeapon)
      m_equippedWeapon->Fire();
  }

	void WeaponComponent::Reload()
	{
		if (m_equippedWeapon)
			m_equippedWeapon->Reload();
	}

	Engine::GameObject* WeaponComponent::CreateBulletGameObject()
  {
    if (!m_equippedWeapon)
      return nullptr;

    BulletFactoryDef def;
    def.Position = Owner.GetTransform()->GetPosition() + Owner.GetTransform()->Forward();
    def.Rotation = Owner.GetTransform()->GetRotation();
    def.Damage = m_equippedWeapon->GetWeaponDamage();
    def.BulletHits = m_rpgComponent->GetStat(RPGStats::AMMO_HITS);
    return GameObjectFactory::CreateBulletObject(def);
  }

	void WeaponComponent::ProcessMessage(const Engine::Message& message)
	{
    if (m_equippedWeapon)
      m_equippedWeapon->ProcessMessage(message);
	}

  void WeaponComponent::AddAmmo(unsigned int additionalAmmo)
  {
    if (m_equippedWeapon)
      m_equippedWeapon->AddAmmo(additionalAmmo);
  }

  unsigned int WeaponComponent::GetMaxAmmo()
  {
    if (m_equippedWeapon)
      return m_equippedWeapon->GetWeaponMaxAmmo();
    
    return 0;
  }

  unsigned int WeaponComponent::GetCurrentAmmo()
  {
    if (m_equippedWeapon)
      return m_equippedWeapon->GetCurrentAmmoCount();

    return 0;
  }

  void WeaponComponent::ReceiveEvent(const event::E_EnemyDied& eventData)
  {
    if (m_rpgComponent)
    {
      AddAmmo(m_rpgComponent->GetStat(RPGStats::AMMO_ON_KILL));
    }
  }

}