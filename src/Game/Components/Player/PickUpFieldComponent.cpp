#include "PickUpFieldComponent.h"
#include "../Actor/ActorComponent.h"
#include "../Actor/RPGComponent.h"
#include "../../Physics/Filters.h"

#include <box2d/b2_circle_shape.h>

namespace Game
{
	PickUpFieldComponent::PickUpFieldComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_fixture(nullptr)
		, m_fixtureShape(nullptr)
	{
		SetRequiredComponents<Engine::PhysicsBodyComponent, ActorComponent, RPGComponent>();
	};

	void PickUpFieldComponent::OnCreate()
	{
		auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
		b2CircleShape circleShape;
		circleShape.m_p.Set(0.0f, 0.0f);
		circleShape.m_radius = Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::PICKUP_FIELD_SIZE);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.categoryBits = physics::EntityCategory::PICKUP_FIELD;
		fixtureDef.filter.maskBits = physics::EntityMask::M_PICKUP_FIELD;
		fixtureDef.isSensor = true;

		m_fixture = physBody->GetB2Body()->CreateFixture(&fixtureDef);
		m_fixtureShape = m_fixture->GetShape();
	}

	void PickUpFieldComponent::Update(float dt)
	{
		if (!m_fixture) return;
		if (!m_fixtureShape) return;

		m_fixtureShape->m_radius = Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::PICKUP_FIELD_SIZE);
	}

	void PickUpFieldComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		viewStrategy->DebugRenderCircle(Engine::ITransform::PositionSpace::WorldSpace, Owner.GetTransform()->GetPosition(), Owner.GetComponent<RPGComponent>()->GetStat(RPGStats::PICKUP_FIELD_SIZE), sf::Color::White);
	}
};