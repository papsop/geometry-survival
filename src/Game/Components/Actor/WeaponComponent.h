#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/Core/Events.h>

#include <queue>
#include <memory>
#include "../../Core/EventData.h"

#include "RPGComponent.h"
#include "IBulletMiddleware.h"

namespace Game
{
	struct WeaponData;

	class WeaponComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:

		WeaponComponent(Engine::GameObject& obj);
		~WeaponComponent() override = default;

		void VirtualOnCreate() override;
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

		void SetTargetPosition(Engine::math::Vec2 pos) { m_targetPosition = pos; }

		void RegisterBulletMiddleware(IBulletMiddleware* middleware);
		void UnregisterBulletMiddleware(IBulletMiddleware* middleware);

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

	private:
		RPGComponent* m_rpgComponent;
		std::unique_ptr<WeaponData> m_weapon;
		std::vector<IBulletMiddleware*> m_middlewares;

		float m_reloadTimer = 0.0f;
		unsigned int m_ammo = 0;
		float m_cooldown = 0.0f;
		Engine::math::Vec2 m_targetPosition = {0,0};
	};

}