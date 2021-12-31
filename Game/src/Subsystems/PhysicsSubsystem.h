#pragma once

#include <vector>
#include "../Components/Physics.h"

namespace Game
{
    class SubsystemManager;

    class PhysicsSubsystem
    {
    public:
        ~PhysicsSubsystem();

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


