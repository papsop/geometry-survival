#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/GameObject.h"

#include <box2d/b2_fixture.h>
namespace Engine
{
	class CircleFixtureComponent : public IComponent, public IDebuggable
	{

	public:
		CircleFixtureComponent(GameObject& obj, float radius);
		~CircleFixtureComponent() override;	

		void OnCreate() override;
		void Update(float dt) override {};
		void OnCollisionStart(GameObject& other) override {};


		void Debug(view::IViewStrategy* viewStrategy) override;

	private:
		float m_radius;
		b2Fixture* m_fixture;
	};
};