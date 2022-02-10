#pragma once
#include "../Core/Events.h"

#include <unordered_map>
#include <vector>
namespace Engine
{
    class Application;
    class EventManager
    {
    public:
        static EventManager& Get();
        ~EventManager() = default;

        template<typename T>
        void RegisterEventListener(IEvent* listener)
        {
            uint32_t ID = IEvent::GetEventID<T>();
            
            if (m_listeners.find(ID) == m_listeners.end())
            { // first listener for this event
                m_listeners.insert(std::pair<uint32_t, std::vector<void*>>(ID, {}));
            }

            m_listeners[ID].emplace_back(listener);
        }

        template<typename T>
        void UnregisterEventListener(IEvent* listener)
        {
            uint32_t ID = IEvent::GetEventID<T>();

            if (m_listeners.find(ID) != m_listeners.end())
            {
                auto& listeners = m_listeners[ID];
                listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
            }

        }

    private:
        EventManager();
        std::unordered_map<uint32_t, std::vector<void*>> m_listeners;

    friend class Application;
    };
}
