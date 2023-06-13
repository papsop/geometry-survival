#pragma once
#include "IManager.h"
#include "../Components/Physics.h"
#include "../Components/Core.h"
#include "../Core/Events.h"

#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <vector>
#include <array>
namespace Engine
{
	struct CollisionData
	{
		GameObject* Other;
		b2Filter OtherFilter;
		b2Filter MyFilter;
	};

	enum class CollisionType 
	{
		START, END
	};

	struct CachedCollisionEntry
	{
		CollisionType Type;
		GameObjectID TargetID;
		GameObjectID OtherID;
		b2Filter MyFilter;
		b2Filter OtherFilter;
	};

	class PhysicsManager : public IManager, public b2ContactListener, public IEventListener<event::E_ApplicationStopped>
	{
	public:
		~PhysicsManager() = default;
		static PhysicsManager& Get();

		void RegisterComponent(PhysicsBodyComponent* component);
		void UnregisterComponent(PhysicsBodyComponent* component);

		void Update(float dt) override;
		void FixedUpdate(float dt) override;
		b2Body* CreateBody(const b2BodyDef* def);
		void DeleteBody(b2Body* body);

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override { /* no implementation */ };
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override { /* no implementation */ };

		void ReceiveEvent(const event::E_ApplicationStopped& eventData) override;

		float GetFixedUpdate() const { return m_fixedUpdate; }

		void SetPhysicsEnabled(bool val) { m_physicsEnabled = val; }
		bool GeyPhysicsEnabled() { return m_physicsEnabled; }
	private:
		PhysicsManager() = default;
		
		bool m_physicsEnabled = true;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void ProcessCachedCollisions();

		std::unique_ptr<b2World> m_b2World;
		std::vector<PhysicsBodyComponent*> m_physicsBodies;	

		std::queue< CachedCollisionEntry > m_cachedCollisions;

		const float m_fixedUpdate = 1.0f/120.0f;

	friend class Application;
	};
}