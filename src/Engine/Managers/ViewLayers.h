#pragma once

namespace Engine
{
	namespace view
	{
		enum class Layer
		{
			BACKGROUND				= 0,
			EXPERIENCE_GLOBE	= 1,
			ENEMY							= 2,
			BULLET						= 3,
			PLAYER						= 4,
			UI								= 5,

			// always last
			COUNT,
		};
	};
}