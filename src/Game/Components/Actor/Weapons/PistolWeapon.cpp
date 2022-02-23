#include "PistolWeapon.h"
#include <Engine/Debug/Logger.h>

namespace Game
{
    void PistolWeapon::Fire()
    {
        if (m_currentShootingCooldown <= 0.0f)
        {
            LOG_WARN("Shooting pistol");
            m_currentShootingCooldown = m_shootingCooldown;
        }
            
    }
}