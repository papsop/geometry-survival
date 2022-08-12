#pragma once
#include "EventData.h"
#include "../Managers/EventManager.h"

#include <stdint.h>


namespace Engine
{
    template<typename T>
    class IEventListener
    {
    public:
        IEventListener()
        {
            EventManager::Get().RegisterEventListener<T>(this);
        }
        ~IEventListener()
        {
            EventManager::Get().UnregisterEventListener<T>(this);
        }

    protected:
        virtual void ReceiveEvent(const T& eventData) = 0;

    friend class EventManager;
    };
}


