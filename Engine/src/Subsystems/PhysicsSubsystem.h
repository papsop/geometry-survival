#pragma once
#include "../Components/Physics.h"
#include <vector>

namespace Engine
{
    class PhysicsSubsystem
    {
    public:
        ~PhysicsSubsystem() = default;

        void RegisterComponent(RigidbodyComponent *c);

        void UnregisterComponent(RigidbodyComponent* c);

        void Update(float dt);

    private:
        PhysicsSubsystem();
        std::vector< RigidbodyComponent* > m_rigidbodies;

    friend class SubsystemManager;
    };
}