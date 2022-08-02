#pragma once
#include <Engine/Components/Core.h>
#include "Weapons/IWeapon.h"

namespace Game
{
    class WeaponComponent : public Engine::IComponent
    {
    public:
        WeaponComponent(Engine::GameObject& obj);
        ~WeaponComponent() override;

        void OnCreate() override;
        void Update(float dt) override;

        void Fire();
        void Reload();
        
        void EquipWeapon(std::unique_ptr<IWeapon> weapon);
        Engine::GameObject* CreateBulletGameObject();

        void ProcessMessage(const Engine::Message& message) override;

    private:
		std::unique_ptr<IWeapon> m_equippedWeapon;
    };

};

