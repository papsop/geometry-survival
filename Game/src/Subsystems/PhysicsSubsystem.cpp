#include "PhysicsSubsystem.h"

#include "../Core/GameObject.h"
#include "../Debug/Logger.h"

namespace Game
{
    PhysicsSubsystem::PhysicsSubsystem()
        : m_rigidBodies()
        , m_colliders()
    {
        LOG_INFO("Created PhysicsSubsystem");
    }

    PhysicsSubsystem::~PhysicsSubsystem()
    {
        LOG_INFO("Destroyed PhysicsSubsystem");
    }

    void PhysicsSubsystem::RegisterComponent(IComponent* component)
    {
        if (auto rigidbodyComponent = dynamic_cast<RigidbodyComponent*>(component))
        {
            m_rigidBodies.emplace_back(rigidbodyComponent);
            LOG_INFO("{PhysicsSubsystem} registered RigidBodyComponent from ID: %d", rigidbodyComponent->Owner.ID);
        }
    }

    void PhysicsSubsystem::UnregisterComponent(IComponent* component)
    {
        if (auto rbComp = dynamic_cast<RigidbodyComponent*>(component))
        {
            LOG_INFO("{PhysicsSubsystem} unregistered RigidBodyComponent from ID: %d", rbComp->Owner.ID);
            m_rigidBodies.erase(std::remove(m_rigidBodies.begin(), m_rigidBodies.end(), rbComp), m_rigidBodies.end());
        }
    }

    void PhysicsSubsystem::Update(float dt)
    {
        // Update collider components
        for (auto cC : m_colliders)
            cC->Update(dt);

        // Update rigidbody components
        for (auto rbC : m_rigidBodies)
            rbC->Update(dt);
    }
};