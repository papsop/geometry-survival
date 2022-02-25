#include "PistolWeapon.h"
#include <Engine/Debug/Logger.h>
#include "../WeaponComponent.h"

namespace Game
{
    void PistolWeapon::Fire()
    {
        if (m_currentShootingCooldown <= 0.0f)
        {
            ownerWeaponComponent->CreateBulletGameObject();
            m_currentShootingCooldown = m_shootingCooldown;
        }
            
    }
}