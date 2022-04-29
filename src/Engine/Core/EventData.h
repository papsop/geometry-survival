#pragma once
#include "GameObject.h"

namespace Engine
{
    struct E_GameObjectDeleted
    {
        E_GameObjectDeleted(GameObjectID id) : ID(id) {};
        GameObjectID ID;
    };

	struct E_ApplicationStopped
	{
	};
}