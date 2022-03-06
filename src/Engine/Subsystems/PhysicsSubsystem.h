#pragma once
#include "../Components/Physics.h"
#include "../Components/Core.h"

#include <vector>
#include <array>
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

        bool CheckCollision(CircleColliderData a, CircleColliderData b);

        std::vector< RigidbodyComponent* > m_rigidbodies;
        
        std::array<std::vector< IColliderComponent* >, static_cast<size_t>(IColliderComponent::CollisionLayer::COUNT)> m_colliders;

    friend class SubsystemManager;
    };
}