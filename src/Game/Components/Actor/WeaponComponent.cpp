#include "WeaponComponent.h"
#include "ActorComponent.h"
#include "BulletComponent.h"
#include "../SplashScreen/SplashShape.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Managers/SubsystemManager.h>
#include <Engine/Subsystems/ViewSubsystem.h>
#include <Engine/Components/Physics.h>

namespace Game
{
    WeaponComponent::WeaponComponent(Engine::GameObject& obj)
        : IComponent(obj)
    {
        Requires<ActorComponent>();
    }

    void WeaponComponent::OnCreate()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    WeaponComponent::~WeaponComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }


    void WeaponComponent::Update(float dt)
    {
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

    Engine::GameObject* WeaponComponent::CreateBulletGameObject()
    {
        auto bullet = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::PROJECTILE, "Bullet");
        bullet->GetTransform().Position = Owner.GetTransform().Position;
        bullet->GetTransform().Scale = { 0.2f, 0.2f };
        bullet->AddComponent<Engine::RigidbodyComponent>();
        bullet->GetComponent<Engine::RigidbodyComponent>()->Velocity = { Owner.GetTransform().Forward().x * 800, Owner.GetTransform().Forward().y * 800};
        
        bullet->AddComponent<Engine::CircleColliderComponent>(10.0f);
        // TODO: remove this
        bullet->AddComponent<SplashShape>(4, sf::Color::Magenta, Engine::SubsystemManager::Get().GetViewSubsystem().GetZIndexFromPool() );

        // TODO: make this renderable
        bullet->AddComponent<BulletComponent>();

        Owner.GetScene().AddGameObject(bullet->c_ID);
        return bullet;
    }
    
}