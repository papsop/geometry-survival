#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/GameObject/GameObject.h"

#include <box2d/b2_fixture.h>
namespace Engine
{
	struct CircleFixtureDef
	{
		float Radius;
		bool IsSensor = false;
	};

	class CircleFixtureComponent : public IComponent, public IDebuggableComponent
	{

	public:
		CircleFixtureComponent(GameObject& obj, const CircleFixtureDef& def);
		~CircleFixtureComponent() override;

		void VirtualOnCreate() override;
		void Update(float dt) override {};

		void Debug(VisualDebugContext& debugContext) override;

	private:
		float m_radius;
		bool m_isSensor;
		b2Fixture* m_fixture;
	};
}