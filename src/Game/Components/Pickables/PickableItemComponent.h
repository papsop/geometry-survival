#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Components/Physics/PhysicsBodyComponent.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/Signal.h>

#include "../../Core/EventData.h"
namespace Game
{
	class PickableItemComponent: public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		PickableItemComponent(Engine::GameObject& obj);
		~PickableItemComponent() override = default;
		void VirtualOnCreate() override;
		void OnDestroy() override;

		void OnCollisionStart(Engine::CollisionData& collision) override;
		void Update(float dt) override;

		Engine::Signal<Engine::GameObject*> OnMarked;
		Engine::Signal<Engine::GameObject*> OnPickedUp;

	protected:
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
	private:
		Engine::GameObject* m_markedBy;
		Engine::PhysicsBodyComponent* m_physBodyComponent;
	};
};