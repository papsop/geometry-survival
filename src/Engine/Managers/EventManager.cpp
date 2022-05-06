#include "EventManager.h"
#include "../Application.h"

namespace Engine
{

    EventManager& EventManager::Get() 
    {
        return Application::Instance().GetEventManager();
    }

}