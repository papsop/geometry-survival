#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
	class GameOverMenuComponent : public Engine::IImGuiComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
	{
	public:
		GameOverMenuComponent(Engine::GameObject& obj);
		~GameOverMenuComponent() override = default;

		void Update(float dt) override;

		// Button callbacks
		void NewGameButtonCallback();
		void BackToMenuButtonCallback();

	protected:
		void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	private:
		void HandleSwitchToMainMenu();
	};
}