#include "PhysicsBodyComponent.h"

#include "../../Managers/SubsystemManager.h"
#include "../../Core/GameObject.h"
#include "../../Utils/AllUtils.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

namespace Engine
{

	PhysicsBodyComponent::PhysicsBodyComponent(GameObject& obj, b2BodyType bodyType)
		: IComponent(obj)
	{
		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position = Owner.GetTransform().Position;
		m_b2Body = SubsystemManager::Get().GetPhysicsSubsystem().CreateBody(&bodyDef);
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