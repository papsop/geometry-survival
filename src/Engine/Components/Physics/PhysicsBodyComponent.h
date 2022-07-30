#pragma once
#include "../Core.h"
#include <box2d/b2_body.h>

namespace Engine
{

	struct PhysicsBodyDef
	{
		b2BodyType	BodyType		= b2_staticBody;
		bool		IsBullet		= false;
		uint16		CategoryBits	= 0x0000; // I'm xxx
		uint16		MaskBits		= 0x0000; // I collide with yyy
	};

	class PhysicsBodyComponent : public IComponent
	{
	public:
		PhysicsBodyComponent(GameObject& obj, PhysicsBodyDef& def);
		~PhysicsBodyComponent() override;

		void Update(float dt) override;
		void OnCreate() override;

		b2Body* GetB2Body() { return m_b2Body; }

		void ApplyImpulseToCenter(const math::Vec2& impulse);
		void ApplyTorque(float torque);
		b2Vec2 GetLinearVelocity() { return m_b2Body->GetLinearVelocity(); }
		float GetMass() { return m_b2Body->GetMass(); }

		uint16 GetCategoryBits() { return m_categoryBits; }
		uint16 GetMaskBits() { return m_maskBits; }
	private:
		b2Body* m_b2Body = nullptr;
		b2BodyType m_bodyType;
		bool m_isBullet;
		uint16 m_categoryBits;
		uint16 m_maskBits;

	friend class SceneSerializer;
	protected:
		void VirtualOnActivated() override;


		void VirtualOnDeactivated() override;

	};
}
