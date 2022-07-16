#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/GameObject/GameObject.h"

#include <box2d/b2_fixture.h>
namespace Engine
{
	struct TriangleFixtureDef
	{
		float Radius;

	};

	class TriangleFixtureComponent : public IComponent, public IDebuggableComponent
	{

	public:
		TriangleFixtureComponent(GameObject& obj, TriangleFixtureDef& def);
		~TriangleFixtureComponent() override;

		void OnCreate() override;
		void Update(float dt) override {};
		void OnCollisionStart(GameObject* other) override {};

		void Debug(view::IViewStrategy* viewStrategy) override;

	private:
		b2Fixture* m_fixture;
	};
};