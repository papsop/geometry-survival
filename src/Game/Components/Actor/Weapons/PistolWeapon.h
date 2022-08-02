#pragma once
#include "IWeapon.h"

namespace Game
{
    class PistolWeapon : public IWeapon
    {
    public:
        PistolWeapon(WeaponComponent& weaponComponent);
        ~PistolWeapon() = default;
    };
}
