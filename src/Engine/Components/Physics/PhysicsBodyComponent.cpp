#include "PhysicsBodyComponent.h"

#include "../../Managers/SubsystemManager.h"
#include "../../Core/GameObject.h"
#include "../../Utils/AllUtils.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

namespace Engine
{

	PhysicsBodyComponent::PhysicsBodyComponent(GameObject& obj, const b2BodyDef* bodyDef)
		: IComponent(obj)
		, m_b2Body(SubsystemManager::Get().GetPhysicsSubsystem().CreateBody(bodyDef))
	{
		b2CircleShape circleShape;
		circleShape.m_p = Owner.GetTransform().Position; //position, relative to body position
		circleShape.m_radius = 5; //radius

		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 0.3f;

		m_b2Body->CreateFixture(&myFixtureDef);
	}

	void PhysicsBodyComponent::OnCreate()
	{
		SubsystemManager::Get().GetPhysicsSubsystem().RegisterComponent(this);
	}

	PhysicsBodyComponent::~PhysicsBodyComponent()
	{
		SubsystemManager::Get().GetPhysicsSubsystem().UnregisterComponent(this);
	}

	void PhysicsBodyComponent::Update(float dt)
	{
		Owner.GetTransform().Position = m_b2Body->GetPosition();
	}
};