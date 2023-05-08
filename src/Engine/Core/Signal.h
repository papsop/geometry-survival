#pragma once

namespace Engine
{
	class Signal
	{
	public:
		Signal() = default;
		~Signal() = default;

		template<typename T>
		void AddListener(T* listener, void(T::* func)())
		{
			m_listeners.push_back([=]() { (listener->*func)(); });
		}

		void RemoveListener(void* listener)
		{
			m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), [=](std::function<void()> func)
				{
				return func.target<void(*)()>() == listener;
			}), m_listeners.end());
		}

		void Invoke()
		{
			for (auto& listener : m_listeners)
			{
				listener();
			}
		}
	private:
		std::vector<std::function<void()>> m_listeners;
	};
}