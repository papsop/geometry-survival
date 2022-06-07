#pragma once

namespace Engine
{

	enum MessageType
	{
		MSG_Test
	};


	class GameObject;

	struct Message
	{
		MessageType Type;
		GameObject* Sender;
	};
}