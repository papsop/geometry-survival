#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {}

    void PhysicsSubsystem::RegisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.emplace_back(c);
    }

    void PhysicsSubsystem::RegisterComponent(IColliderComponent* c)
    {
        m_colliders.emplace_back(c);
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), c), m_rigidbodies.end());
    }

    void PhysicsSubsystem::UnregisterComponent(IColliderComponent* c)
    {
        m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), c), m_colliders.end());
    }

    void PhysicsSubsystem::Update(float dt)
    {
        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
               c->Update(dt);
    }
}