#pragma once
#include "EventData.h"
#include "../Managers/EventManager.h"

#include <stdint.h>


namespace Engine
{

    template<typename T>
    class IEventDispatcher
    {
    public:

        IEventDispatcher() = default;
        virtual ~IEventDispatcher() = default;

        virtual void DispatchEvent(const T eventData)
        {
            EventManager::Instance().DispatchEvent<T>(eventData);
        };
    };

    template<typename T>
    class IEventListener
    {
    public:
        
        IEventListener()
        {
            EventManager::Instance().RegisterEventListener<T>(this);
        }

        ~IEventListener()
        {
            EventManager::Instance().UnregisterEventListener<T>(this);
        }

        virtual void ReceiveEvent(const T& eventData) = 0;
    };
}


