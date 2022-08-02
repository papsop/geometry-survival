#include "WeaponPistol_Shootable.h"
#include "Weapon_Cooldown.h"

namespace Game
{
	WeaponPistol_Shootable::WeaponPistol_Shootable(Engine::FiniteStateMachine& parentStateMachine, WeaponComponent& weaponComponent)
		: IState(parentStateMachine)
		, m_ownerWeaponComponent(weaponComponent)
	{
	}

	void Game::WeaponPistol_Shootable::Update(float dt)
	{
		/* */
	}

	void Game::WeaponPistol_Shootable::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MSG_Weapon_Fire)
		{
			auto& ownerGO = m_ownerWeaponComponent.Owner;
			auto* bullet = m_ownerWeaponComponent.CreateBulletGameObject();
			auto forward = ownerGO.GetTransform().Forward();
			forward *= 30.0f;
			bullet->GetComponent<Engine::PhysicsBodyComponent>()->ApplyImpulseToCenter(forward);
			m_parentStateMachine.TransitionTo<Weapon_Cooldown<WeaponPistol_Shootable>>();
		}
	}


};
