#include "WeaponComponent.h"
#include "ActorComponent.h"
#include "BulletComponent.h"

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
    Engine::ITransform::TransformDefinition transformDef;
    transformDef.Position = Owner.GetTransform()->GetPosition() + Owner.GetTransform()->Forward();
    transformDef.Rotation = Owner.GetTransform()->GetRotation();

    auto bullet = Engine::GameObjectManager::Get().CreateGameObject("Bullet", Engine::GameObjectTag::PLAYER_BULLET, transformDef);


    Engine::PhysicsBodyDef physBodyDef;
    physBodyDef.BodyType = b2_dynamicBody;
    physBodyDef.IsBullet = true;
    physBodyDef.CategoryBits = physics::EntityCategory::PLAYER_BULLET;
    physBodyDef.MaskBits = physics::EntityMask::M_PLAYER_BULLET;

    bullet->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);


    Engine::ShapeViewDef shapeViewDef;
    shapeViewDef.Color = sf::Color::Blue;
    shapeViewDef.PointCount = 3;
    shapeViewDef.Radius = 0.5f;
    shapeViewDef.Layer = Engine::view::Layer::BULLET;

    Engine::CircleFixtureDef circleFixtureDef;
    circleFixtureDef.Radius = 0.5f;
    circleFixtureDef.IsSensor = true;

    bullet->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
    bullet->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);

    BulletDef bulletDef;
    bulletDef.Damage = m_equippedWeapon->GetWeaponDamage();
    bulletDef.BulletHits = m_rpgComponent->GetStat(RPGStats::AMMO_HITS);
    bullet->AddComponent<BulletComponent>(bulletDef);

    return bullet;
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