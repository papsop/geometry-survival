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

    IEventListener<event::E_ApplicationStopped>::RegisterListener();
	}

	void PhysicsManager::VirtualOnDestroy()
	{
		m_b2World = nullptr;

		IEventListener<event::E_ApplicationStopped>::UnregisterListener();
	}

	void PhysicsManager::ProcessCachedCollisions()
	{
		while (!m_cachedCollisions.empty())
		{
			CachedCollisionEntry cachedCollision = m_cachedCollisions.front();
			m_cachedCollisions.pop();

			auto* targetObject = GameObjectManager::Get().GetGameObjectByID(cachedCollision.TargetID);
			auto* otherObject = GameObjectManager::Get().GetGameObjectByID(cachedCollision.OtherID);

			if(!targetObject)
				continue; // Target object doesn't live anymore

			CollisionData data;
			data.MyFilter = cachedCollision.MyFilter;
			data.OtherFilter = cachedCollision.OtherFilter;
			data.Other = otherObject;

			switch (cachedCollision.Type)
			{
			case CollisionType::START:
				targetObject->OnCollisionStart(data);
				break;
			case CollisionType::END:
				targetObject->OnCollisionEnd(data);
				break;
			default:
				LOG_ERROR("Unknown collision type");
				break;
			}
		}
	}

	void PhysicsManager::RegisterComponent(PhysicsBodyComponent* component)
	{
		EnsureLocked();
		m_physicsBodies.emplace_back(component);
	}

	void PhysicsManager::UnregisterComponent(PhysicsBodyComponent* component)
	{
		EnsureLocked();
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
		
		if (bodyA == bodyB) return;

		CachedCollisionEntry entryObjectA;
		entryObjectA.TargetID = bodyA->GetUserData().pointer;
		entryObjectA.OtherID= bodyB->GetUserData().pointer;
		entryObjectA.MyFilter = contact->GetFixtureA()->GetFilterData();
		entryObjectA.OtherFilter = contact->GetFixtureB()->GetFilterData();
		entryObjectA.Type = CollisionType::START;

		CachedCollisionEntry entryObjectB;
		entryObjectB.TargetID = bodyB->GetUserData().pointer;
		entryObjectB.OtherID = bodyA->GetUserData().pointer;
		entryObjectB.MyFilter = contact->GetFixtureB()->GetFilterData();
		entryObjectB.OtherFilter = contact->GetFixtureA()->GetFilterData();
		entryObjectB.Type = CollisionType::START;

		m_cachedCollisions.push(entryObjectA);
		m_cachedCollisions.push(entryObjectB);
	}

	void PhysicsManager::EndContact(b2Contact* contact)
	{
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();

		if (bodyA == bodyB) return;

		CachedCollisionEntry entryObjectA;
		entryObjectA.TargetID = bodyA->GetUserData().pointer;
		entryObjectA.OtherID = bodyB->GetUserData().pointer;
		entryObjectA.MyFilter = contact->GetFixtureA()->GetFilterData();
		entryObjectA.OtherFilter = contact->GetFixtureB()->GetFilterData();
		entryObjectA.Type = CollisionType::END;

		CachedCollisionEntry entryObjectB;
		entryObjectB.TargetID = bodyB->GetUserData().pointer;
		entryObjectB.OtherID = bodyA->GetUserData().pointer;
		entryObjectB.MyFilter = contact->GetFixtureB()->GetFilterData();
		entryObjectB.OtherFilter = contact->GetFixtureA()->GetFilterData();
		entryObjectB.Type = CollisionType::END;

		m_cachedCollisions.push(entryObjectA);
		m_cachedCollisions.push(entryObjectB);
	}

	void PhysicsManager::ReceiveEvent(const event::E_ApplicationStopped& eventData)
	{
		m_b2World->SetContactListener(nullptr);
	}

	void PhysicsManager::Update(float dt)
	{
		if (!m_physicsEnabled)
			return;

		Lock();
		for (auto& body : m_physicsBodies)
		{
			if (body->ShouldUpdate())
			{
				body->Update(dt);
			}
		}
		Unlock();
	}

	void PhysicsManager::FixedUpdate(float dt)
	{
		if (!m_physicsEnabled)
			return;

		Lock();
		m_b2World->Step(dt, 8, 3);

		ProcessCachedCollisions(); // sends OnCollisionXXX

		for (auto& body : m_physicsBodies)
		{
			if (body->ShouldUpdate())
			{
				body->FixedUpdate(dt);
			}
		}
		Unlock();
	}

}