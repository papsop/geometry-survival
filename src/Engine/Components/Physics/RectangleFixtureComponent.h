#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/GameObject.h"

namespace Engine
{
	class RectangleFixtureComponent : public IComponent, public IDebuggable
	{
	public:
		RectangleFixtureComponent(GameObject& obj);
		~RectangleFixtureComponent() override;

		void OnCreate() override;
		void Update(float dt) override {};
		void OnCollision(GameObject& other) override {};
		
		void Debug(view::IViewStrategy* viewStrategy) override;
	private:
		b2Fixture* m_fixture;
	};
}