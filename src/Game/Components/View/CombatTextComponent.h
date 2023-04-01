#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"
namespace Game
{
	class CombatTextComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		CombatTextComponent(Engine::GameObject& obj, float duration);
		~CombatTextComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;
		void Update(float dt) override;

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

	private:
		float m_durationLeft;
		float m_initialDuration;
	};
}