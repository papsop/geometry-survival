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
        void Reload();      // ask to reload gun
        void RefillAmmo();  // ask to refill all the ammo
        
        void EquipWeapon(std::unique_ptr<IWeapon> weapon);
        Engine::GameObject* CreateBulletGameObject();

	private:
		std::unique_ptr<IWeapon> m_equippedWeapon;
    };

};

