#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/Events.h>

#include <queue>
#include <memory>
#include "../../Core/EventData.h"

#include "RPGComponent.h"
#include "Weapons.h"

namespace Game
{

	class WeaponComponent : public Engine::IComponent
	{
	public:
		WeaponComponent(Engine::GameObject& obj);
		~WeaponComponent() override = default;

		void OnCreate() override;
		void Update(float dt) override;

		void Fire();
		void Reload();

		unsigned int GetAmmo() const;
		unsigned int GetMaxAmmo() const;

		void EquipWeapon(std::unique_ptr<WeaponData> weapon);
	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	private:
		RPGComponent* m_rpgComponent;
		std::unique_ptr<WeaponData> m_weapon;
	};

}