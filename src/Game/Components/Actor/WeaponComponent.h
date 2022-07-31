#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>
#include "Weapons/IWeapon.h"

namespace Game
{
    class WeaponComponent : public Engine::IComponent, public Engine::IDebuggableComponent
    {
    public:
        WeaponComponent(Engine::GameObject& obj);
        ~WeaponComponent() override;

        void OnCreate() override;
        void Update(float dt) override;

        void Fire();
        
        void EquipWeapon(std::unique_ptr<IWeapon> weapon);
        Engine::GameObject* CreateBulletGameObject();

        void Debug(Engine::view::IViewStrategy* viewStrategy) override;
	private:
		std::unique_ptr<IWeapon> m_equippedWeapon;
    };

};

