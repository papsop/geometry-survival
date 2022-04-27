#pragma once
#include "../Components/Physics.h"
#include "../Components/Core.h"

#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <vector>
#include <array>
namespace Engine
{
    class PhysicsSubsystem : public b2ContactListener
    {
    public:
        ~PhysicsSubsystem() = default;

        void RegisterComponent(PhysicsBodyComponent* component);
        void UnregisterComponent(PhysicsBodyComponent* component);

        void Update(float dt);
        b2Body* CreateBody(const b2BodyDef* def);

        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    private:
        PhysicsSubsystem();
        

        std::unique_ptr<b2World> m_b2World;
        std::vector<PhysicsBodyComponent*> m_physicsBodies;

    friend class SubsystemManager;
    };
}