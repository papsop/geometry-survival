#pragma once
#include "../Components/Physics.h"
#include "../Components/Core.h"

#include <box2d/b2_world.h>

#include <vector>
#include <array>
namespace Engine
{
    class PhysicsSubsystem
    {
    public:
        ~PhysicsSubsystem() = default;

        void RegisterComponent(PhysicsBodyComponent* component);
        void UnregisterComponent(PhysicsBodyComponent* component);

        void Update(float dt);
        b2Body* CreateBody(const b2BodyDef* def);

    private:
        PhysicsSubsystem();
        

        std::unique_ptr<b2World> m_b2World;
        std::vector<PhysicsBodyComponent*> m_physicsBodies;

    friend class SubsystemManager;
    };
}