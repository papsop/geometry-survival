#include "RectangleFixtureComponent.h"

namespace Engine
{
	RectangleFixtureComponent::RectangleFixtureComponent(GameObject & obj)
		: IComponent(obj)
	{
		Requires<PhysicsBodyComponent>();
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
		//viewStrategy->DebugRenderCircle(Owner.GetTransform().Position, m_radius, sf::Color::Red);
	}
}