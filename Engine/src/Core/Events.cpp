#include "Events.h"
#include "../Application.h"
namespace Engine
{
    uint32_t IEvent::m_nextEventID = 0;


    IGameObjectDeletedListener::IGameObjectDeletedListener()
    {
        EventManager::Get().RegisterEventListener<IGameObjectDeletedListener>(this);
    }

    IGameObjectDeletedListener::~IGameObjectDeletedListener()
    {
        EventManager::Get().UnregisterEventListener<IGameObjectDeletedListener>(this);
    }

}