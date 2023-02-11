#pragma once
#include "IManager.h"
#include "../Utils/IdGenerator.h"
#include "../Debug/Logger.h"

#include <unordered_map>
#include <vector>

namespace Engine
{
    template<typename>
    class IEventListener;

    template<typename>
    class IEventDispatcher;

    class EventManager : public IManager
    {
    public:
      static EventManager& Get();
      ~EventManager() = default;

      template<typename T>
      void RegisterEventListener(IEventListener<T>*listener);

      template<typename T>
      void UnregisterEventListener(IEventListener<T>*listener);

      template<typename T>
      void DispatchEvent(const T eventData);

    private:
      EventManager() = default;
      std::unordered_map<uint32_t, std::vector<void*>> m_listeners;

    template<typename>
    friend class IEventDispatcher;
    friend class Application;
    };
}

#include "EventManager.inl"