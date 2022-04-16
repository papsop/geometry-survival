#pragma once
#include "../Core.h"

#include <box2d/b2_body.h>

namespace Engine
{
	class PhysicsBodyComponent : public IComponent
	{
	public:
		PhysicsBodyComponent(GameObject& obj, const b2BodyDef* bodyDef);
		~PhysicsBodyComponent() override;

		void Update(float dt) override;
		void OnCreate() override;
		void OnCollision(GameObject& other) override {};

		b2Body* GetB2Body() { return m_b2Body; }
	private:
		b2Body* m_b2Body;
	};
}
