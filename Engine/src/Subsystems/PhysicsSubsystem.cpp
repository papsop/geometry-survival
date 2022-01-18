#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {}

    void PhysicsSubsystem::RegisterComponent(RigidbodyComponent* component)
    {
        m_rigidbodies.emplace_back(component);
        LOG_INFO("registered RigidbodyComponent from ID: %d", component->Owner.ID);
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* component)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), component), m_rigidbodies.end());
        LOG_INFO("unregistered RigidbodyComponent from ID: %d", component->Owner.ID);
    }

    void PhysicsSubsystem::Update(float dt)
    {
        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
               c->Update(dt);
    }
}