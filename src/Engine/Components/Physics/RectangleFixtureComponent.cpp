#include "RectangleFixtureComponent.h"

#include <box2d/b2_polygon_shape.h>
namespace Engine
{
	RectangleFixtureComponent::RectangleFixtureComponent(GameObject & obj)
		: IComponent(obj)
	{
		Requires<PhysicsBodyComponent>();
	}

	void RectangleFixtureComponent::OnCreate()
	{
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(10.0f, 1.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		m_fixture = Owner.GetComponent<PhysicsBodyComponent>()->GetB2Body()->CreateFixture(&fixtureDef);
	}

	RectangleFixtureComponent::~RectangleFixtureComponent()
	{
		// body destroys all the fixtures when it's deleted
	}

	void RectangleFixtureComponent::Debug(view::IViewStrategy* viewStrategy)
	{
		//viewStrategy->DebugRenderCircle(Owner.GetTransform().Position, 2.0f, sf::Color::Green);
	}
}