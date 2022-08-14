#include "PhysicsManager.h"
#include "../Debug/Logger.h"
#include "../Core/GameObject/GameObject.h"

#include "../Application.h"
#include "../Components/Physics.h"
#include "../Managers/GameObjectManager.h"
#include <box2d/b2_body.h>


namespace Engine
{
	Engine::PhysicsManager& PhysicsManager::Get()
	{
		return Application::Instance().GetPhysicsManager();
	}
	
	void PhysicsManager::VirtualOnInit()
	{
		b2Vec2 gravity(0.f, 0.0f);// -2.f);// -9.8f);
		m_b2World = std::make_unique<b2World>(gravity);
		m_b2World->SetContactListener(this);
	}

	void PhysicsManager::VirtualOnDestroy()
	{
		m_b2World = nullptr;
	}

	void PhysicsManager::RegisterComponent(PhysicsBodyComponent* component)
	{
		m_physicsBodies.emplace_back(component);
	}

	void PhysicsManager::UnregisterComponent(PhysicsBodyComponent* component)
	{
		DD_ASSERT(m_b2World != nullptr, "b2World doesn't exist");
		m_physicsBodies.erase(std::remove(m_physicsBodies.begin(), m_physicsBodies.end(), component), m_physicsBodies.end());
	}

	b2Body* PhysicsManager::CreateBody(const b2BodyDef* def)
	{
		DD_ASSERT(m_b2World != nullptr, "b2World doesn't exist");
		return m_b2World->CreateBody(def);
	}

	void PhysicsManager::DeleteBody(b2Body* body)
	{
		DD_ASSERT(m_b2World != nullptr, "b2World doesn't exist");
		m_b2World->DestroyBody(body);
	}

	void PhysicsManager::BeginContact(b2Contact* contact)
	{
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();
		
		GameObject* objA = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);
		GameObject* objB = GameObjectManager::Get().GetGameObjectByID(bodyB->GetUserData().pointer);

		CollisionData collisionDataA;
		collisionDataA.Other = objB;
		collisionDataA.OtherFilter = contact->GetFixtureB()->GetFilterData();

		CollisionData collisionDataB;
		collisionDataB.Other = objA;
		collisionDataB.OtherFilter = contact->GetFixtureA()->GetFilterData();

		if (objA) objA->OnCollisionStart(collisionDataA);
		if (objB) objB->OnCollisionStart(collisionDataB);
	}

	void PhysicsManager::EndContact(b2Contact* contact)
	{
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();

		GameObject* objA = GameObjectManager::Get().GetGameObjectByID(bodyA->GetUserData().pointer);
		GameObject* objB = GameObjectManager::Get().GetGameObjectByID(bodyB->GetUserData().pointer);

		CollisionData collisionDataA;
		collisionDataA.Other = objA;
		collisionDataA.OtherFilter = contact->GetFixtureA()->GetFilterData();

		CollisionData collisionDataB;
		collisionDataB.Other = objB;
		collisionDataB.OtherFilter = contact->GetFixtureA()->GetFilterData();

		// One of the object could have been deleted after BeginContact
		if (objA) objA->OnCollisionEnd(collisionDataA);
		if (objB) objB->OnCollisionEnd(collisionDataB);
	}

	void PhysicsManager::ReceiveEvent(const event::E_ApplicationStopped& eventData)
	{
		m_b2World->SetContactListener(nullptr);
	}

	void PhysicsManager::Update(float dt)
	{
		m_b2World->Step(dt, 8, 3);

		for (auto& body : m_physicsBodies)
			body->Update(dt);
	}
}