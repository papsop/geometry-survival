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
        LOG_DEBUG("registered RigidbodyComponent from ID: %d", component->Owner.c_ID);
    }

    void PhysicsSubsystem::UnregisterComponent(RigidbodyComponent* component)
    {
        m_rigidbodies.erase(std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), component), m_rigidbodies.end());
        LOG_DEBUG("unregistered RigidbodyComponent from ID: %d", component->Owner.c_ID);
    }

    void PhysicsSubsystem::Update(float dt)
    {
        for (auto c : m_rigidbodies)
            if (c->Owner.ShouldUpdate())
               c->Update(dt);
    }
}