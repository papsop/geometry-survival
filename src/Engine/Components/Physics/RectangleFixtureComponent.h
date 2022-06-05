#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../utils/VectorUtils.h"

namespace Engine
{
	struct RectangleFixtureDef
	{
		math::Vec2 Size;
		float Density = 1.0f;
		float Friction = 1.0f;
	};

	class RectangleFixtureComponent : public IComponent, public IDebuggableComponent
	{
	public:
		RectangleFixtureComponent(GameObject& obj, const RectangleFixtureDef& def);
		~RectangleFixtureComponent() override;

		void OnCreate() override;
		void Update(float dt) override {};
		void OnCollisionStart(GameObject* other) override {};
		
		void Debug(view::IViewStrategy* viewStrategy) override;
	private:
		b2Fixture* m_fixture;
		math::Vec2 m_fixtureShapeSize;
	};
}