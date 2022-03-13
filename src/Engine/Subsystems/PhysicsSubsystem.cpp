#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

#include "../Components/Physics.h"

namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {
    }

    void PhysicsSubsystem::RegisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.emplace_back(c);
    }

    void PhysicsSubsystem::RegisterComponent(IColliderComponent* c)
    {
        auto& layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.emplace_back(c);
        if(!m_qtree)
            m_qtree = std::make_unique<QTree>(sf::Rect(0.0f, 0.0f, 1024.0f, 768.0f));

        if (c->GetColliderData().CircleColliders.size() > 0)
        {
            auto boundingBox = c->GetColliderData().CircleColliders[0].GetBoundingBox();
            m_qtree->Insert(c->Owner.c_ID, boundingBox);
        }
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* c)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), c), m_rigidbodies.end());
    }

    void PhysicsSubsystem::UnregisterComponent(IColliderComponent* c)
    {
        auto& layerArray = m_colliders[static_cast<size_t>(c->c_layer)];
        layerArray.erase(std::remove(layerArray.begin(), layerArray.end(), c), layerArray.end());
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

    void PhysicsSubsystem::Update(float dt)
    {
        for (auto& layer : m_colliders)
        {
            for (auto& colliderA : layer)
            {
                colliderA->Update(dt);
                auto colliderAData = colliderA->GetColliderData();
                for (auto& colliderB : layer)
                {
                    if (colliderA == colliderB) continue;
                    auto colliderBData = colliderB->GetColliderData();
                    for (auto& circleColliderA : colliderAData.CircleColliders)
                    {
                        for (auto& circleColliderB : colliderBData.CircleColliders)
                        {
                            if (CheckCollision(circleColliderA, circleColliderB))
                            {
                                // notify A
                                colliderA->Owner.OnCollision(colliderB->Owner);
                            }
                        }
                    }
                    

                }
            }
        }
            

        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
               c->Update(dt);
    }
}