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

		// General ui input events
		// - things like fire/movement/etc. should be handled in InputComponent
		struct E_OnMenuKeyClicked {};
	}
}