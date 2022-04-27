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
		auto physBody = Owner.GetComponent<PhysicsBodyComponent>();
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(10.0f, 1.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.categoryBits = physBody->GetCategoryBits();
		fixtureDef.filter.maskBits = physBody->GetMaskBits();

		m_fixture = Owner.GetComponent<PhysicsBodyComponent>()->GetB2Body()->CreateFixture(&fixtureDef);
	}

	RectangleFixtureComponent::~RectangleFixtureComponent()
	{
		// body destroys all the fixtures when it's deleted
	}

	void RectangleFixtureComponent::Debug(view::IViewStrategy* viewStrategy)
	{
		viewStrategy->DebugRenderRectangle(Owner.GetTransform().Position, math::Vec2(10.0f, 1.0f), m_fixture->GetBody()->GetAngle(), sf::Color::Green);
	}
}