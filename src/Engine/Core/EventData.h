#pragma once
#include "GameObject.h"

namespace Engine
{
    struct GameObjectDeletedData
    {
        GameObjectDeletedData(GameObjectID id) : ID(id) {};
        GameObjectID ID;
    };
}