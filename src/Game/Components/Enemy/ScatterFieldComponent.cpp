#include "ScatterFieldComponent.h"
#include "EnemyComponent.h"

#include "../../Physics/Filters.h"

#include "../Actor/BulletComponent.h"
#include "../Player/PlayerComponent.h"

#include <box2d/b2_circle_shape.h>

#include <Engine/Managers/GameObjectManager.h>
namespace Game
{
	ScatterFieldComponent::ScatterFieldComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_fixture(nullptr)
		, m_enemies()
	{
		SetRequiredComponents<Engine::PhysicsBodyComponent, EnemyComponent>();
	};

	void ScatterFieldComponent::OnCreate()
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

	void ScatterFieldComponent::Update(float dt)
	{

	}

	std::vector<Engine::GameObject*> ScatterFieldComponent::GetValidEnemyTargets()
	{
		std::vector<Engine::GameObject*> result;

		auto& GO_Manager = Engine::GameObjectManager::Get();
		for (auto& enemy_ID : m_enemies)
		{
			auto* enemy_GO = GO_Manager.GetGameObjectByID(enemy_ID);
			if (enemy_GO)
			{
				result.emplace_back(enemy_GO);
			}
		}

		return result;
	}

	void ScatterFieldComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		m_enemies.insert(collision.Other->ID);
	}

	void ScatterFieldComponent::OnCollisionEnd(Engine::CollisionData& collision)
	{
		if (collision.Other) // might got destroyed
		{
			m_enemies.erase(collision.Other->ID);
		}
	}

	void ScatterFieldComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		viewStrategy->DebugRenderCircle(Engine::ITransform::PositionSpace::WorldSpace, Owner.GetTransform()->GetPosition(), m_radius, sf::Color::White);

		for (auto& enemy : GetValidEnemyTargets())
		{
			viewStrategy->DebugRenderLine(Engine::ITransform::PositionSpace::WorldSpace,
				Owner.GetTransform()->GetPosition(),
				enemy->GetTransform()->GetPosition(),
				sf::Color::Green
			);
		}
	}

};