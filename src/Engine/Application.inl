#include "Application.h"

namespace Engine
{
	template<typename T,
		typename ... Args,
		typename>
	void Application::RegisterManager(Args&& ... args)
	{
		auto manager = std::make_unique<T>(std::forward(args) ...);
		manager->OnInit();
		m_gameManagers.push(std::move(manager));
	}
}