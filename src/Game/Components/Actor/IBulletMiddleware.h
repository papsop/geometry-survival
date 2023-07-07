#pragma once

namespace Engine
{
	class GameObject;
}

namespace Game
{

	class WeaponComponent;

	// Don't forget to register/unregister to weaponOwner
	class IBulletMiddleware
	{
	public:
		IBulletMiddleware() = default;
		virtual ~IBulletMiddleware() = default;

		virtual void Middleware(Engine::GameObject& bullet) = 0;
	};
}