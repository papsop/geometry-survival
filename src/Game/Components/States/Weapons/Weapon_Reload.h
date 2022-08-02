#pragma once
#include <Engine/Core/StateMachine/IState.h>
#include "../../Actor/WeaponComponent.h"

namespace Game
{
	template<typename T>
	class Weapon_Reload : public Engine::IState
	{
	public:
		Weapon_Reload(Engine::FiniteStateMachine& parentStateMachine, WeaponComponent& weaponComponent);
		~Weapon_Reload() = default;


		void Update(float dt) override;


		void OnTransitionIn() override;

	private:
		void TransitionBackToT();

		WeaponComponent& m_ownerWeaponComponent;
		float m_currentTimer;
		float m_reloadTimer;
	};
}

#include "Weapon_Reload.inl"