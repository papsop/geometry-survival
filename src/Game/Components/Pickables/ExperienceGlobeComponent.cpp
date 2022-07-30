#include "ExperienceGlobeComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Managers/ComponentManager.h>
#include "../../Physics/Filters.h"

namespace Game
{
	ExperienceGlobeComponent::ExperienceGlobeComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_markedBy(nullptr)
	{
		SetRequiredComponents<Engine::CircleFixtureComponent, Engine::PhysicsBodyComponent>();
	}	
	
	void ExperienceGlobeComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	ExperienceGlobeComponent::~ExperienceGlobeComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void ExperienceGlobeComponent::Update(float dt)
	{
		if (m_markedBy != nullptr)
		{
			auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
			auto mass = physBody->GetMass();

			auto actualVelocity = physBody->GetLinearVelocity();
			auto dir = Engine::math::V2fNormalize(m_markedBy->GetTransform().Position - Owner.GetTransform().Position);

			dir *= 40.0f;
			auto desiredVelocity = dir;

			auto impulse = (desiredVelocity - actualVelocity);
			impulse *= mass;
			physBody->ApplyImpulseToCenter(impulse);
		}
	}

	void ExperienceGlobeComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		if (collision.OtherFilter.categoryBits == physics::EntityCategory::PICKUP_FIELD
			&& m_markedBy == nullptr)
		{ // only 1 pickup field can mark experience globe
			m_markedBy = collision.Other;
		}
		else if (collision.OtherFilter.categoryBits == physics::EntityCategory::PLAYER)
		{ // actual pickup
			Owner.Destroy();
		}
	}

};