#include "RectangleFixtureComponent.h"

#include <box2d/b2_polygon_shape.h>
namespace Engine
{
	RectangleFixtureComponent::RectangleFixtureComponent(GameObject & obj, const RectangleFixtureDef& def)
		: IComponent(obj)
		, m_fixtureShapeSize(def.Size)
	{
		SetRequiredComponents<PhysicsBodyComponent>();

		auto physBody = Owner.GetComponent<PhysicsBodyComponent>();
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(def.Size.x, def.Size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = def.Density;
		fixtureDef.friction = def.Friction;
		fixtureDef.filter.categoryBits = physBody->GetCategoryBits();
		fixtureDef.filter.maskBits = physBody->GetMaskBits();

		m_fixture = Owner.GetComponent<PhysicsBodyComponent>()->GetB2Body()->CreateFixture(&fixtureDef);
	}

	void RectangleFixtureComponent::OnCreate()
	{
	}

	RectangleFixtureComponent::~RectangleFixtureComponent()
	{
		// body destroys all the fixtures when it's deleted
	}

	void RectangleFixtureComponent::Debug(view::IViewStrategy* viewStrategy)
	{
		if (!m_isActive)
			return;

		viewStrategy->DebugRenderRectangle(Owner.GetTransform().Position, m_fixtureShapeSize, m_fixture->GetBody()->GetAngle(), sf::Color::Green);
	}
}