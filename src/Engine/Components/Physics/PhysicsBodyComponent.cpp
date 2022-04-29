#include "PhysicsBodyComponent.h"

#include "../../Managers/SubsystemManager.h"
#include "../../Core/GameObject.h"
#include "../../Utils/AllUtils.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

namespace Engine
{

	PhysicsBodyComponent::PhysicsBodyComponent(GameObject& obj, PhysicsBodyDef& def)
		: IComponent(obj)
		, m_categoryBits(def.CategoryBits)
		, m_maskBits(def.MaskBits)
	{
		b2BodyDef bodyDef;
		bodyDef.type = def.BodyType;
		bodyDef.position = Owner.GetTransform().Position;
		bodyDef.bullet = def.IsBullet;
		//bodyDef.fixedRotation = true;
		bodyDef.userData.pointer = Owner.c_ID;
		m_b2Body = SubsystemManager::Get().GetPhysicsSubsystem().CreateBody(&bodyDef);
	}

	void PhysicsBodyComponent::OnCreate()
	{
		SubsystemManager::Get().GetPhysicsSubsystem().RegisterComponent(this);
	}

	void PhysicsBodyComponent::ApplyImpulseToCenter(const math::Vec2& impulse)
	{
		m_b2Body->ApplyLinearImpulse(impulse, m_b2Body->GetWorldCenter(), true);
	}

	void PhysicsBodyComponent::ApplyTorque(float torque)
	{
		m_b2Body->ApplyTorque(torque, true);
	}

	PhysicsBodyComponent::~PhysicsBodyComponent()
	{
		SubsystemManager::Get().GetPhysicsSubsystem().UnregisterComponent(this);
	}

	void PhysicsBodyComponent::Update(float dt)
	{
		Owner.GetTransform().Position = m_b2Body->GetPosition();
		Owner.GetTransform().Rotation = m_b2Body->GetAngle();
	}
};