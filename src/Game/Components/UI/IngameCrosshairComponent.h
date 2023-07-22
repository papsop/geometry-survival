#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <Engine/Managers/InputManager.h>
#include <Engine/Managers/RenderManager.h>
#include <Engine/Managers/ComponentManager.h>

#include <Engine/Core/Events.h>
#include "../../Core/EventData.h"

namespace Game
{
	class IngameCrosshairComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		IngameCrosshairComponent(Engine::GameObject& obj);
		~IngameCrosshairComponent() override;

		void Update(float dt) override;

		void VirtualOnCreate() override;

	protected:
		void ReceiveEvent(const event::E_GameStateChanged & eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;
	private:
		Engine::InputManager& m_inputManager;
	};
}