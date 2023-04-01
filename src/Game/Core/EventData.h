#pragma once

namespace Engine
{
	class GameObject;
}

namespace Game
{
	enum class GameState
	{
		Gameplay,
		Paused
	};

	namespace event
	{
		struct E_GameStateChanged
		{
			GameState NewState;
		};

		struct E_PlayerLeveledUp
		{

		};

		struct E_PlayerObjectRegistrationChanged
		{
			Engine::GameObject* PlayerObject;		// new player object
			bool Registered;										// registered/unregistered
		};

		struct E_EnemyDied{};
		struct E_PlayerDied{};
    struct E_PlayerTookDamage{};
	}
}