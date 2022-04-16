#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

#include "../Components/Physics.h"
#include <box2d/b2_body.h>


namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {
        b2Vec2 gravity(0, -9.8);
        m_b2World = std::make_unique<b2World>(gravity);
    }

	void PhysicsSubsystem::RegisterComponent(PhysicsBodyComponent* component)
	{
        m_physicsBodies.emplace_back(component);
	}

	void PhysicsSubsystem::UnregisterComponent(PhysicsBodyComponent* component)
	{
        DD_ASSERT(m_b2World != nullptr, "b2World doesn't exist");
        m_b2World->DestroyBody(component->GetB2Body());
        m_physicsBodies.erase(std::remove(m_physicsBodies.begin(), m_physicsBodies.end(), component), m_physicsBodies.end());
	}

    b2Body* PhysicsSubsystem::CreateBody(const b2BodyDef* def)
    {
        DD_ASSERT(m_b2World != nullptr, "b2World doesn't exist");
        m_b2World->CreateBody(def);
    }

    void PhysicsSubsystem::Update(float dt)
    {
        m_b2World->Step(dt, 8, 3);

        m_b2World->GetBodyList();

        for (auto& body : m_physicsBodies)
            body->Update(dt);
    }
}