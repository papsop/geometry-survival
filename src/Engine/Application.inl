#include "Application.h"
#include "Utils/IdGenerator.h"

namespace Engine
{
	template<typename T,
		typename ... Args,
		typename>
	void Application::RegisterGameManager(Args&& ... args)
	{
		auto managerID = IdGenerator<Application>::GetID<T>();

		if (m_managers.find(managerID) == m_managers.end())
		{
			m_managers[managerID] = std::make_unique<T>(*this, std::forward(args) ...);
			m_managers[managerID]->OnInit();
		}
	}
	template<typename T,
		typename
	>
	T* Application::GetGameManager()
	{
		auto managerID = IdGenerator<Application>::GetID<T>();
		if (m_managers.find(managerID) != m_managers.end())
		{
			return static_cast<T*>(m_managers[managerID].get());
		}
		else
			return nullptr;
	}
}