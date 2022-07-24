#pragma once

namespace Engine
{

	enum MessageType
	{
		MSG_Test,
		MSG_DIED
	};


	class GameObject;

	struct Message
	{
		MessageType Type;
		GameObject* Sender;
	};
}