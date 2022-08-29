#include "WeaponPistol_Shootable.h"
#include "../../Actor/Weapons/PistolWeapon.h"
namespace Game
{
	WeaponPistol_Shootable::WeaponPistol_Shootable(Engine::PushdownStateMachine& parentStateMachine, PistolWeapon& pistol)
		: IState(parentStateMachine)
		, m_ownerPistol(pistol)
	{

	}


	void WeaponPistol_Shootable::OnTransitionIn()
	{
		m_ownerPistol.SetWeaponState(IWeapon::WeaponState::Shootable);
	}

	void WeaponPistol_Shootable::Update(float dt)
	{
		
	}

	void WeaponPistol_Shootable::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MessageType::Weapon_Fire)
		{
			m_ownerPistol.Fire();
		}
	}

};