#pragma once
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>

namespace Game
{
    class WeaponComponent;
    class IWeapon : public Engine::IDebuggableComponent
    {
    public:
        IWeapon(WeaponComponent& weaponComponent)
            : m_ownerWeaponComponent(weaponComponent) {}
        ~IWeapon() = default;

        // all weapons share these
        void Fire();
        bool HasAmmo();
        bool IsOffCooldown();
        bool CanFire();
        void Reload();
        void Update(float dt);

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
        void ProcessMessage(const Engine::Message& message);

        virtual void VirtualFire() = 0;

        float GetWeaponCooldown();
        float GetWeaponDamage();
        float GetWeaponMaxAmmo();
    protected:
        WeaponComponent& m_ownerWeaponComponent;
        Engine::PushdownStateMachine m_stateMachine;
        // Derived weapon class should set these
        float m_shotsPerSecond = 3.0f;
        float m_reloadTime = 1.0f;
        int m_currentAmmo = 0;
        int m_maxAmmo = 0;
        float m_weaponDamage = 1.0f;

    // internal variables for every weapon
    private:
        float m_currentCooldown;
        
    friend class WeaponComponent;
    };
}

