#include "WeaponComponent.h"
#include "ActorComponent.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>

namespace Game
{
    WeaponComponent::WeaponComponent(Engine::GameObject& obj)
        : IComponent(obj)
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);

        Requires<ActorComponent>();
    }

    WeaponComponent::~WeaponComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void WeaponComponent::OnGameObjectChanged(){}

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
}