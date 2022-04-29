#include "EventManager.h"

namespace Engine
{

    EventManager& EventManager::Instance() 
    {
        static EventManager instance;
		return instance;
    }

    EventManager::EventManager()
    {

    }

}