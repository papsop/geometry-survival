#include "PhysicsSubsystem.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject.h"

#include "../Application.h"
#include "../Components/Physics.h"
#include "../Managers/GameObjectManager.h"
#include <box2d/b2_body.h>


namespace Engine
{
    PhysicsSubsystem::PhysicsSubsystem()
    {
        b2Vec2 gravity(0.f, 0.0f);// -2.f);// -9.8f);
        m_b2World = std::make_unique<b2World>(gravity);
		m_b2World->SetContactListener(this);
    }

	PhysicsSubsystem::~PhysicsSubsystem()
	{
		LOG_WARN("Deleting PhysicsSubsystem");
		m_b2World = nullptr; // delete
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

	void PhysicsSubsystem::BeginContact(b2Contact* contact)
	{
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();

		GameObject* objA = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);
		GameObject* objB = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);

		if (objA != nullptr && objB != nullptr)
		{
			objA->OnCollisionStart(*objB);
			objB->OnCollisionStart(*objA);
		}
	}

	void PhysicsSubsystem::EndContact(b2Contact* contact)
	{
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();

		GameObject* objA = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);
		GameObject* objB = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);

		if (objA != nullptr && objB != nullptr)
		{
			objA->OnCollisionEnd(*objB);
			objB->OnCollisionEnd(*objA);
		}
	}

	void PhysicsSubsystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{

	}

	void PhysicsSubsystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{

	}

	void PhysicsSubsystem::ReceiveEvent(const E_ApplicationStopped& eventData)
	{
		m_b2World->SetContactListener(nullptr);
	}

	void PhysicsSubsystem::Update(float dt)
    {
		m_b2World->Step(dt, 8, 3);

		for (auto& body : m_physicsBodies)
			body->Update(dt);
    }
}