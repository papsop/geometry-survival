#pragma once
#include <Engine/Core/GameObject/GameObject.h>

#include <type_traits>
#include <functional>
namespace Game
{

	class WeaponComponent;

	class BulletHandler
	{
	public:
		BulletHandler(WeaponComponent& ownerWeapon);

		template<typename T>
		void RegisterMiddleware(T* listener, void(T::* func)())
		{
			m_middlewares.push_back([=]() { (listener->*func)(); });
		}

		void UnregisterMiddleware(void* listener)
		{
			m_middlewares.erase(std::remove_if(m_middlewares.begin(), m_middlewares.end(), [=](std::function<void(Engine::GameObject*)> func)
				{
					return func.target<void(*)()>() == listener;
				}), m_middlewares.end());
		}
	private:
		WeaponComponent& m_ownerWeapon;

		std::vector<std::function<void(Engine::GameObject*)>> m_middlewares;
	};
}