#pragma once
#include "../Utils/IdGenerator.h"

#include <unordered_map>
#include <vector>
namespace Engine
{
    template<typename>
    class IEventListener;

    template<typename>
    class IEventDispatcher;

    class EventManager
    {
    public:
        static EventManager& Instance();
        ~EventManager() = default;

        template<typename T>
        void RegisterEventListener(IEventListener<T>* listener)
        {
            auto ID = IdGenerator<EventManager>::GetID<T>();
            
            if (m_listeners.find(ID) == m_listeners.end())
            { // first listener for this event
                m_listeners.insert(std::pair<uint32_t, std::vector<void*>>(ID, {}));
            }

            m_listeners[ID].emplace_back(static_cast<void*>(listener));
        }

        template<typename T>
        void UnregisterEventListener(IEventListener<T>* listener)
        {
            auto ID = IdGenerator<EventManager>::GetID<T>();

            if (m_listeners.find(ID) != m_listeners.end())
            {
                auto& listeners = m_listeners[ID];
                listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
            }
        }


    private:
        template<typename T>
        void DispatchEvent(const T eventData)
        {
            auto ID = IdGenerator<EventManager>::GetID<T>();

            if (m_listeners.find(ID) != m_listeners.end())
            {
                for (auto& listener : m_listeners[ID])
                {
                    static_cast<IEventListener<T>*>(listener)->ReceiveEvent(eventData);
                }
            }
        }
        EventManager();
        std::unordered_map<uint32_t, std::vector<void*>> m_listeners;

    template<typename>
    friend class IEventDispatcher;
    friend class Application;
    };
}
