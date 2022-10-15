#pragma once

namespace Engine
{
	class GameObject;
}

namespace Game
{
	namespace event
	{
		struct E_GamePaused {};
		struct E_GameResumed {};
		struct E_PlayerLeveledUp
		{

		};

		struct E_OnGameMenu 
		{
			bool IsActive;
		};

		struct E_PlayerObjectRegistrationChanged
		{
			Engine::GameObject* PlayerObject;		// new player object
			bool Registered;										// registered/unregistered
		};
	}
}