#pragma once
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include "../../Actor/Weapons/IWeapon.h"

namespace Game
{
	class Weapon_Reload : public Engine::IState<Engine::PushdownStateMachine>
	{
	public:
		Weapon_Reload(Engine::PushdownStateMachine& parentStateMachine, IWeapon& weapon, float reloadTime);
		~Weapon_Reload() override = default;

		virtual void Update(float dt);
	private:
		IWeapon& m_ownerWeapon;
		float m_reloadTime;
	};
}