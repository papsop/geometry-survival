#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

#include "../Components/Physics.h"

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
        auto layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.emplace_back(c);
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), c), m_rigidbodies.end());
    }

    void PhysicsSubsystem::UnregisterComponent(IColliderComponent* c)
    {
        auto layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.erase(std::remove(layerArray.begin(), layerArray.end(), c), layerArray.end());
    }

    // Collisions between types of colliders

    bool PhysicsSubsystem::CheckCollision(CircleCollider* a, CircleCollider* b)
    {
        auto posA = a->GetAbsolutePosition();
        auto posB = b->GetAbsolutePosition();

        float distanceSquared = abs(pow(posA.x - posB.x, 2) + pow(posA.y - posB.y, 2));
        float radiiSquared = pow(a->GetRadius() + b->GetRadius(), 2);

        return distanceSquared <= radiiSquared;
    }

    void PhysicsSubsystem::Update(float dt)
    {
        for (auto& layer : m_colliders)
        {
            for (auto& colliderA : layer)
            {
                for (auto& colliderB : layer)
                {
                    // hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
                }

            }
        }
            

        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
               c->Update(dt);
    }
}