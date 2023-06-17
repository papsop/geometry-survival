#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/Core/GameObject/GameObject.h>

#include "../../Core/EventData.h"

namespace Game
{
	class DestroyAfterTimeComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		DestroyAfterTimeComponent(Engine::GameObject& owner, float timeToDie);
		~DestroyAfterTimeComponent();

		void VirtualOnCreate() override;

		void Update(float dt) override;
	private:
		float m_timeToDie = 0.0f;
	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

	};
}