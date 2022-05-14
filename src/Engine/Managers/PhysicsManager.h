#pragma once
#include "IManager.h"
#include "../Components/Physics.h"
#include "../Components/Core.h"
#include "../Core/Events.h"

#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <vector>
#include <array>
namespace Engine
{
	class PhysicsManager : public IManager, public b2ContactListener, public IEventListener<E_ApplicationStopped>
	{
	public:
		~PhysicsManager() = default;
		static PhysicsManager& Get();

		void RegisterComponent(PhysicsBodyComponent* component);
		void UnregisterComponent(PhysicsBodyComponent* component);

		void Update(float dt);
		b2Body* CreateBody(const b2BodyDef* def);
		void DeleteBody(b2Body* body);

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override { /* no implementation */ };
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override { /* no implementation */ };

		void ReceiveEvent(const E_ApplicationStopped& eventData) override;
	private:
		PhysicsManager() = default;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		std::unique_ptr<b2World> m_b2World;
		std::vector<PhysicsBodyComponent*> m_physicsBodies;	
	friend class Application;
	};
}