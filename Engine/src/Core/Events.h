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

        virtual void Dispatch(const T eventData)
        {
            EventManager::Get().DispatchEvent<T>(eventData);
        };
    };

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

        virtual void Receive(const T& eventData) = 0;
    };
}


