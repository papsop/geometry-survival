#pragma once
#include <type_traits>

namespace Engine
{
	template<typename T = void>
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


		// ============== Only for parametrized signals ==============
		template<typename U = T,
						typename = std::enable_if_t<std::is_same_v<U, void> == false>>
		void Invoke(U val)
		{
			for (auto& listener : m_listeners)
			{
				listener(val);
			}
		}

		// ============== Only for void signals ==============
		template<typename U = T,
						 typename = std::enable_if_t<std::is_same_v<U, void> == true>>
			void Invoke()
		{
			for (auto& listener : m_listeners)
			{
				listener();
			}
		}
	private:
		std::vector<std::function<void(T)>> m_listeners;
	};


}