#pragma once

namespace Engine
{

	enum class MessageType
	{
		Transform_Changed,
		Weapon_Fire,
		Weapon_Reload,
		Actor_TookDamage_Knockback,
		Actor_TookDamage_NoKnockback,
	};


	class GameObject;

	struct Message
	{
		MessageType Type;
		GameObject* Sender;
	};
}