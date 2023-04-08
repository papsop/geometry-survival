#include "ExperienceGlobeComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Managers/ComponentManager.h>
#include "../../Physics/Filters.h"
#include "../Player/LevelComponent.h"

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

	void ExperienceGlobeComponent::VirtualOnActivated()
	{
		IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void ExperienceGlobeComponent::VirtualOnDeactivated()
	{
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

	void ExperienceGlobeComponent::Update(float dt)
	{
		if (m_markedBy == nullptr)
			return;

		auto* physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
		float mass = physBody->GetMass();

		auto actualVelocity = physBody->GetLinearVelocity();
		auto dir = Engine::math::V2fNormalize(m_markedBy->GetTransform()->GetPosition() - Owner.GetTransform()->GetPosition());

		dir *= 40.0f;
		auto desiredVelocity = dir;

		auto impulse = (desiredVelocity - actualVelocity);
		impulse *= mass;
		physBody->ApplyImpulseToCenter(impulse);
	}

	void ExperienceGlobeComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		if (collision.OtherFilter.categoryBits == physics::EntityCategory::PICKUP_FIELD
			&& m_markedBy == nullptr)
		{ // only 1 pickup field can mark experience globe
			m_markedBy = collision.Other;
		}
		else if (collision.OtherFilter.categoryBits == physics::EntityCategory::PLAYER)
		{ 
			// levelComponent destroys it when picked up
			auto levelComponent = collision.Other->GetComponent<LevelComponent>();
			if (levelComponent)
			{
				levelComponent->ApplyExperience(10.0f);
			}
			Owner.Destroy();
		}
	}	

	void ExperienceGlobeComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
	}
};