#pragma once

namespace Engine
{

	enum MessageType
	{
		MSG_Test,
		MSG_DIED,
		MSG_Weapon_Fire,
		MSG_Weapon_Reload
	};


	class GameObject;

	struct Message
	{
		MessageType Type;
		GameObject* Sender;
	};
}