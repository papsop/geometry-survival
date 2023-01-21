#include "BulletFieldComponent.h"
#include "../../Physics/Filters.h"

#include "BulletComponent.h"
#include "../Player/PlayerComponent.h"
#include <box2d/b2_circle_shape.h>

#include <Engine/Managers/GameObjectManager.h>
namespace Game
{
	BulletFieldComponent::BulletFieldComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_fixture(nullptr)
		, m_enemies()
	{
		SetRequiredComponents<Engine::PhysicsBodyComponent, BulletComponent>();
	};

	void BulletFieldComponent::OnCreate()
	{
		auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();

		b2CircleShape circleShape;
		circleShape.m_p.Set(0.0f, 0.0f);
		circleShape.m_radius = m_radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.filter.categoryBits = physics::EntityCategory::PLAYER_BULLET_FIELD;
		fixtureDef.filter.maskBits = physics::EntityMask::M_PLAYER_BULLET_FIELD;
		fixtureDef.isSensor = true;

		m_fixture = physBody->GetB2Body()->CreateFixture(&fixtureDef);
	}

	void BulletFieldComponent::Update(float dt)
	{

	}

	void BulletFieldComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		m_enemies.insert(collision.Other->ID);
	}

	void BulletFieldComponent::OnCollisionEnd(Engine::CollisionData& collision)
	{
		if (collision.Other) // might got destroyed
		{
			m_enemies.erase(collision.Other->ID);
		}
	}

	void BulletFieldComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		viewStrategy->DebugRenderCircle(Engine::ITransform::PositionSpace::WorldSpace, Owner.GetTransform()->GetPosition(), m_radius, sf::Color::White);

		auto& GO_Manager = Engine::GameObjectManager::Get();
		for (auto& enemy_ID : m_enemies)
		{
			auto* enemy_GO = GO_Manager.GetGameObjectByID(enemy_ID);
			if (enemy_GO)
			{
				viewStrategy->DebugRenderLine(Engine::ITransform::PositionSpace::WorldSpace,
					Owner.GetTransform()->GetPosition(),
					enemy_GO->GetTransform()->GetPosition(),
					sf::Color::Green
				);
			}
		}
	}

};