#pragma once
#include "../Managers/GameObjectManager.h"

namespace Engine
{
    struct GameObjectDeletedData
    {
        GameObjectDeletedData(GameObjectID id) : ID(id) {};
        GameObjectID ID;
    };
}