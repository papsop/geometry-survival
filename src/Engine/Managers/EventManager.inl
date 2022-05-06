#include "EventManager.h"

namespace Engine
{
	template<typename T>
	void EventManager::RegisterEventListener(IEventListener<T>* listener)
	{
		auto ID = IdGenerator<EventManager>::GetID<T>();

		if (m_listeners.find(ID) == m_listeners.end())
		{ // first listener for this event
			m_listeners.insert(std::pair<uint32_t, std::vector<void*>>(ID, {}));
		}

		m_listeners[ID].emplace_back(static_cast<void*>(listener));
	}

	template<typename T>
	void EventManager::UnregisterEventListener(IEventListener<T>* listener)
	{
		auto ID = IdGenerator<EventManager>::GetID<T>();

		if (m_listeners.find(ID) != m_listeners.end())
		{
			auto& listeners = m_listeners[ID];
			listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
		}
	}

	template<typename T>
	void EventManager::DispatchEvent(const T eventData)
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
};