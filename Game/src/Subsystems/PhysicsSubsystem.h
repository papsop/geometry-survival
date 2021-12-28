#pragma once
#include <memory>
#include <vector>
#include "../Components/Physics.h"

namespace Game
{
    class SubsystemManager;

    class PhysicsSubsystem
    {
    public:
        ~PhysicsSubsystem() = default;

        void RegisterComponent(IComponent* component);
        void UnregisterComponent(IComponent* component);

        void Update(float dt);

    private:
        PhysicsSubsystem();

        std::vector< BoxCollider* > m_colliders;
        std::vector< RigidbodyComponent* > m_rigidBodies;

    friend class SubsystemManager;
    };
};


