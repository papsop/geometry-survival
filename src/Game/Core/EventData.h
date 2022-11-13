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

		enum PauseState {UNKNOWN, PAUSED, RUNNING};
		struct E_GamePausedChanged 
		{
			PauseState NewState;
		};

		struct E_PlayerObjectRegistrationChanged
		{
			Engine::GameObject* PlayerObject;		// new player object
			bool Registered;										// registered/unregistered
		};

		struct E_EnemyDied
		{

		};
	}
}