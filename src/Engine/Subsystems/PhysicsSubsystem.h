#pragma once
#include "../Components/Physics.h"
#include "../Components/Core.h"
#include <vector>

namespace Engine
{
    class PhysicsSubsystem
    {
    public:
        ~PhysicsSubsystem() = default;

        void RegisterComponent(RigidbodyComponent *c);
        void RegisterComponent(IColliderComponent* c);

        void UnregisterComponent(RigidbodyComponent* c);
        void UnregisterComponent(IColliderComponent* c);

        void Update(float dt);

    private:
        PhysicsSubsystem();
        std::vector< RigidbodyComponent* > m_rigidbodies;
        std::vector< IColliderComponent* > m_colliders;

    friend class SubsystemManager;
    };
}