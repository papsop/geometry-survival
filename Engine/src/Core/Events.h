#pragma once
#include "GameObject.h"
#include <stdint.h>


namespace Engine
{
    class IEvent
    {
    public:
        template<typename T>
        static uint32_t GetEventID()
        {
            static uint32_t eventID = m_nextEventID++;
            return eventID;
        }

        IEvent() = default;
        virtual ~IEvent() = default;
    protected:
        static uint32_t m_nextEventID;
    };

    // Game object manipulation

    class IGameObjectDeletedListener : public IEvent
    {
    public:
        IGameObjectDeletedListener();
        ~IGameObjectDeletedListener();

        //virtual void GameObjectDeletedListener(GameObjectID id) = 0;
    };
}


