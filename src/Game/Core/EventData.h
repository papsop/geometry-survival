#pragma once

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
	}
}