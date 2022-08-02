#pragma once
#include <Engine/Core/StateMachine/IState.h>
#include "../../Actor/WeaponComponent.h"

namespace Game
{
	class WeaponPistol_Shootable : public Engine::IState
	{
	public:
		WeaponPistol_Shootable(Engine::FiniteStateMachine& parentStateMachine, WeaponComponent& weaponComponent);
		~WeaponPistol_Shootable() override = default;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;

	private:
		WeaponComponent& m_ownerWeaponComponent;
	};
};