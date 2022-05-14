#include "EventManager.h"
#include "../Application.h"

namespace Engine
{

    EventManager& EventManager::Get() 
    {
        static EventManager instance;
        return instance;
    }

}