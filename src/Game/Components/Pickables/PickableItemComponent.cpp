#include "PickableItemComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Managers/ComponentManager.h>
#include "../../Physics/Filters.h"

namespace Game
{

	PickableItemComponent::PickableItemComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_markedBy(nullptr)
		, m_physBodyComponent(nullptr)
	{

	}

	void PickableItemComponent::VirtualOnCreate()
	{
		m_physBodyComponent = Owner.GetComponent<Engine::PhysicsBodyComponent>();
	}

	void PickableItemComponent::OnDestroy()
	{

	}

	void PickableItemComponent::Update(float dt)
	{
		if (m_markedBy == nullptr)
			return;

		auto dir = Engine::math::V2fNormalize(m_markedBy->GetTransform()->GetPosition() - Owner.GetTransform()->GetPosition());
		m_physBodyComponent->SetLinearVelocity(dir, 40.0f);
	}

	void PickableItemComponent::OnCollisionStart(Engine::CollisionData& collision)
	{
		if (collision.OtherFilter.categoryBits == physics::EntityCategory::PICKUP_FIELD
			&& m_markedBy == nullptr)
		{ // only 1 pickup field can mark experience globe
			m_markedBy = collision.Other;
			OnMarked.Invoke(m_markedBy);
		}
		else if (collision.OtherFilter.categoryBits == physics::EntityCategory::PLAYER)
		{
			//OnPickedUp.Invoke(m_markedBy);
// 			// levelComponent destroys it when picked up
// 			auto levelComponent = collision.Other->GetComponent<LevelComponent>();
// 			if (levelComponent)
// 			{
// 				levelComponent->ApplyExperience(10.0f);
// 			}
// 			Owner.Destroy();
		}
	}



	void PickableItemComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{

	}

	void PickableItemComponent::VirtualOnActivated()
	{

	}

	void PickableItemComponent::VirtualOnDeactivated()
	{

	}

}