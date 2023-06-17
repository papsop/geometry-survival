#include "CircleFixtureComponent.h"
#include "PhysicsBodyComponent.h"
#include "../../Debug/VisualDebugContext.h"

#include <box2d/b2_circle_shape.h>

namespace Engine
{

	CircleFixtureComponent::CircleFixtureComponent(GameObject& obj, const CircleFixtureDef& def)
		: IComponent(obj)
		, m_radius(def.Radius)
		, m_isSensor(def.IsSensor)
		, m_fixture(nullptr)
	{
		SetRequiredComponents<PhysicsBodyComponent>();
	}

	void CircleFixtureComponent::VirtualOnCreate()
{
		auto physBody = Owner.GetComponent<PhysicsBodyComponent>();
		b2CircleShape circleShape;
		circleShape.m_p.Set(0.0f, 0.0f);
		circleShape.m_radius = m_radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.categoryBits = physBody->GetCategoryBits();
		fixtureDef.filter.maskBits = physBody->GetMaskBits();
		fixtureDef.isSensor = m_isSensor;

		m_fixture = Owner.GetComponent<PhysicsBodyComponent>()->GetB2Body()->CreateFixture(&fixtureDef);
	}

	CircleFixtureComponent::~CircleFixtureComponent()
	{
		// body destroys all the fixtures when it's deleted
	}	
	
  void CircleFixtureComponent::Debug(VisualDebugContext& debugContext)
  {
		debugContext.DebugRenderCircle(ITransform::PositionSpace::WorldSpace, Owner.GetTransform()->GetPosition(), m_radius, sf::Color::Red);
  }

};


