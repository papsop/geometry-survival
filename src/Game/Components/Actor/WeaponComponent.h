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
	class WeaponComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		WeaponComponent(Engine::GameObject& obj);
		~WeaponComponent() override = default;

		void OnCreate() override;
		void Update(float dt) override;

		void Fire();
		void FinishReload();
		void InitiateTimedReload();

		bool IsOnCooldown() const;
		bool HasAmmo() const;
		bool IsReloading() const;
		bool IsFireable() const;

		float GetReloadTimer() const;
		float GetReloadCompletion() const;
		unsigned int GetAmmo() const;
		unsigned int GetMaxAmmo() const;

		void EquipWeapon(std::unique_ptr<WeaponData> weapon);

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

	private:
		RPGComponent* m_rpgComponent;
		std::unique_ptr<WeaponData> m_weapon;

		float m_reloadTimer = 0.0f;
		unsigned int m_ammo = 0;
		float m_cooldown = 0.0f;
	};

}