#include "CircleFixtureComponent.h"
#include "PhysicsBodyComponent.h"

#include <box2d/b2_circle_shape.h>
namespace Engine
{

	CircleFixtureComponent::CircleFixtureComponent(GameObject& obj, float radius)
		: IComponent(obj)
		, m_radius(radius)
		, m_fixture(nullptr)
	{
		Requires<PhysicsBodyComponent>();
	}

	void CircleFixtureComponent::OnCreate() 
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

		m_fixture = Owner.GetComponent<PhysicsBodyComponent>()->GetB2Body()->CreateFixture(&fixtureDef);
	}

	CircleFixtureComponent::~CircleFixtureComponent()
	{
		// body destroys all the fixtures when it's deleted
	}
	
	void CircleFixtureComponent::Debug(view::IViewStrategy* viewStrategy)
	{
		viewStrategy->DebugRenderCircle(Owner.GetTransform().Position, m_radius, sf::Color::Red);
	}

};


