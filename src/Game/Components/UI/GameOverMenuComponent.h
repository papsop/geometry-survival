#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
	class GameOverMenuComponent : public Engine::IUIComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
	{
	public:
		GameOverMenuComponent(Engine::GameObject& obj);
		~GameOverMenuComponent() override = default;


		// Button callbacks
		void NewGameButtonCallback();
		void BackToMenuButtonCallback();

	protected:
		void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;
		void RegisterUIElements() override;
		void UIShown() override;
		void UIHidden() override;

	private:
		void HandleSwitchToMainMenu();

		tgui::VerticalLayout::Ptr m_menuLayout;

		tgui::Button::Ptr m_newGameButton;
		tgui::Button::Ptr m_backToMenuButton;
	};
}