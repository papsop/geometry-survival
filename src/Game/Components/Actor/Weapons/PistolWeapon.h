#pragma once
#include "IWeapon.h"

namespace Game
{
    class PistolWeapon : public IWeapon
    {
    public:
        PistolWeapon(WeaponComponent* weaponComponent)
            : IWeapon(weaponComponent) 
        {
            m_shootingCooldown = 0.1f;
        }
        ~PistolWeapon() = default;
        
        void Fire() override;
    };
}
