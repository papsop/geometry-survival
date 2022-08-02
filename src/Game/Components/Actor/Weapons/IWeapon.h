#pragma once
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Core/StateMachine/FiniteStateMachine.h>

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
        void RefillAmmo();
        void Update(float dt);

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
        void ProcessMessage(const Engine::Message& message);

    protected:
        WeaponComponent& m_ownerWeaponComponent;
        Engine::FiniteStateMachine m_stateMachine;
        // Derived weapon class should set these

        float m_currentShootingCooldown = 0.0f;
        float m_shootingCooldown = 1.0f;

        int m_currentAmmo = 0;
        int m_maxAmmo = 0;
        
    friend class WeaponComponent;
    };
}

