#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"
namespace Game
{
	class ExperienceGlobeComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		ExperienceGlobeComponent(Engine::GameObject& obj);
		~ExperienceGlobeComponent() override = default;
		void VirtualOnCreate() override;
		void OnDestroy() override;

		void OnCollisionStart(Engine::CollisionData& other) override;
		void Update(float dt) override;
	protected:
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
	private:
		Engine::GameObject* m_markedBy;
	};
};