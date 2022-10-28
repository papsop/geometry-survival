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
    IEventListener() = default;
    ~IEventListener() = default;
  protected:
    virtual void ReceiveEvent(const T& eventData) = 0;
    
    void RegisterListener()
    {
      EventManager::Get().RegisterEventListener<T>(this);
    }

    void UnregisterListener()
    {
      EventManager::Get().UnregisterEventListener<T>(this);
    }

    friend class EventManager;
  };
}
