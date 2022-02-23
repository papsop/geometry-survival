#pragma once
namespace Game
{
    class WeaponComponent;
    class IWeapon
    {
    public:
        IWeapon(WeaponComponent* weaponComponent)
            : ownerWeaponComponent(weaponComponent){}
        ~IWeapon() = default;

        virtual void Fire() = 0;

        void Update(float dt)
        {
            m_currentShootingCooldown -= dt;
        }

    protected:
        WeaponComponent* ownerWeaponComponent;
        float m_currentShootingCooldown = 0.0f;
        float m_shootingCooldown = 1.0f; // derived class should change this
    };
}

