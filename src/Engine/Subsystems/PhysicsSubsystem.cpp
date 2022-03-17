#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

#include "../Components/Physics.h"

namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {
    }

    // Component registration

    void PhysicsSubsystem::RegisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.emplace_back(c);
    }

    void PhysicsSubsystem::RegisterComponent(IColliderComponent* c)
    {
        auto& layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.emplace_back(c);
        InsertCollider(c);
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), c), m_rigidbodies.end());
    }

    void PhysicsSubsystem::UnregisterComponent(IColliderComponent* c)
    {
        auto& layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.erase(std::remove(layerArray.begin(), layerArray.end(), c), layerArray.end());
        RemoveCollider(c);
    }

    // ======================================================================

    void PhysicsSubsystem::InsertCollider(IColliderComponent* c)
    {
        if (!m_qtree)
            m_qtree = std::make_unique<QTree<IColliderComponent>>(sf::Rect(0.0f, 0.0f, 1024.0f, 768.0f)); // config

        auto colliderData = c->GetColliderData();
        for (CircleColliderData ccd : colliderData.CircleColliders)
        {
            m_qtree->Insert(c, ccd.GetBoundingBox());
        }
        
    }

    void PhysicsSubsystem::RemoveCollider(IColliderComponent* c)
    {
        if (m_qtree)
            m_qtree->Remove(c);
    }

    // Collisions between types of colliders

    bool PhysicsSubsystem::CheckCollision(CircleColliderData a, CircleColliderData b)
    {
        auto posA = a.Position;
        auto posB = b.Position;

        float distanceSquared = abs(powf(posA.x - posB.x, 2) + powf(posA.y - posB.y, 2));
        float radiiSquared = powf(a.Radius + b.Radius, 2);

        return distanceSquared <= radiiSquared;
    }


    bool PhysicsSubsystem::CheckColliderComponentsCollision(const IColliderComponent* a, const IColliderComponent* b)
    {
        if (a == b) return false;
        bool result = false;
        auto colliderData_A = a->GetColliderData();
        auto colliderData_B = b->GetColliderData();

        for (auto& circleColliderA : colliderData_A.CircleColliders)
        {
            for (auto& circleColliderB : colliderData_B.CircleColliders)
            {
                if (CheckCollision(circleColliderA, circleColliderB))
                    result = true;
            }
        }

        return result;
    }

    void PhysicsSubsystem::Update(float dt)
    {
        // order?

        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
                c->Update(dt);

        for (auto& layer : m_colliders)
        {
            for (auto& collider : layer)
            {
                collider->Update(dt);
                if (collider->IsDirty())
                {
                    RemoveCollider(collider);
                    InsertCollider(collider);
                }
            }
        }

        for (auto& layer : m_colliders)
        {
            for (auto& colliderA : layer)
            {
                colliderA->Update(dt);
                auto colliderAData = colliderA->GetColliderData();
                for (auto circle : colliderAData.CircleColliders)
                {
                    auto possibleIntersections = m_qtree->FindPossibleIntersections(circle.GetBoundingBox());
                    for (auto& colliderB : possibleIntersections)
                    {
                        if (CheckColliderComponentsCollision(colliderA, colliderB))
                        {
                            colliderA->Owner.OnCollision(colliderB->Owner);
                        }
                    }
                }
            }
        }
    }
}