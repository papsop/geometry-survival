#pragma once
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Actor/WeaponComponent.h"

namespace Game
{
	class PistolWeapon;

	class WeaponPistol_Shootable : public Engine::IState<Engine::PushdownStateMachine>
	{
	public:
		WeaponPistol_Shootable(Engine::PushdownStateMachine& parentStateMachine, PistolWeapon& pistol);
		~WeaponPistol_Shootable() override = default;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;

	private:
		PistolWeapon& m_ownerPistol;

		float m_cooldown = 1.0f;
		float m_currentCooldown = 0.0f;
	};
};