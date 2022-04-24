#pragma once
#include "../Core.h"

#include <box2d/b2_body.h>

namespace Engine
{
	class PhysicsBodyComponent : public IComponent
	{
	public:
		PhysicsBodyComponent(GameObject& obj, b2BodyType bodyType);
		~PhysicsBodyComponent() override;

		void Update(float dt) override;
		void OnCreate() override;
		void OnCollision(GameObject& other) override {};

		b2Body* GetB2Body() { return m_b2Body; }

		void ApplyImpulseToCenter(const math::Vec2& impulse);
		b2Vec2 GetLinearVelocity() { return m_b2Body->GetLinearVelocity(); }
		float GetMass() { return m_b2Body->GetMass(); }
	private:
		b2Body* m_b2Body;
	};
}
