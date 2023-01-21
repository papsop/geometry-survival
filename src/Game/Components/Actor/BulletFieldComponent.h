#pragma once
#include <set>
#include <Engine/Components/Core.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/IDebuggable.h>

namespace Game
{
	class BulletFieldComponent : public Engine::IComponent, public Engine::IDebuggableComponent
	{
	public:
		BulletFieldComponent(Engine::GameObject& obj);
		~BulletFieldComponent() = default;

		void OnCreate() override;
		void Update(float dt) override;

		void OnCollisionStart(Engine::CollisionData& collision) override;
		void OnCollisionEnd(Engine::CollisionData& collision) override;

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
	private:
		float m_radius = 20.0f;
		b2Fixture* m_fixture;
		std::set<Engine::GameObjectID> m_enemies;
	};
}
