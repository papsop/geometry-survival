#include "PistolWeapon.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Components/Physics.h>
#include "../WeaponComponent.h"

namespace Game
{
    void PistolWeapon::Fire()
    {
        if (m_currentShootingCooldown <= 0.0f)
        {
            auto& owner = ownerWeaponComponent->Owner;
            auto* bullet = ownerWeaponComponent->CreateBulletGameObject();
            auto forward = owner.GetTransform().Forward();
            forward *= 30.0f;
            bullet->GetComponent<Engine::PhysicsBodyComponent>()->ApplyImpulseToCenter(forward);
            
            m_currentShootingCooldown = m_shootingCooldown;
        }   
    }
}