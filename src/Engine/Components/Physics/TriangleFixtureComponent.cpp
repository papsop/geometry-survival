#include "TriangleFixtureComponent.h"

namespace Engine
{

	TriangleFixtureComponent::TriangleFixtureComponent(GameObject& obj, TriangleFixtureDef& def)
		: IComponent(obj)
	{
		SetRequiredComponents<PhysicsBodyComponent>();
	}

	TriangleFixtureComponent::~TriangleFixtureComponent()
	{

	}

	void TriangleFixtureComponent::VirtualOnCreate()
{

	}

	void TriangleFixtureComponent::Debug(view::IViewStrategy* viewStrategy)
	{

	}

};