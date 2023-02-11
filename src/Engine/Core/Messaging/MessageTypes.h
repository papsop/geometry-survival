#pragma once

namespace Engine
{

	enum class MessageType
	{
		Transform_Changed,
		Weapon_Fire,
		Weapon_Reload,
		Actor_TookDamage
	};


	class GameObject;

	struct Message
	{
		MessageType Type;
		GameObject* Sender;
	};
}