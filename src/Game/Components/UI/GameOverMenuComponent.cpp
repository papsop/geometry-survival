#include "GameOverMenuComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"
#include "../../Managers/GameManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/Application.h>
namespace Game
{

	GameOverMenuComponent::GameOverMenuComponent(Engine::GameObject& obj)
		: IUIComponent(obj)
	{
	}


	void GameOverMenuComponent::RegisterUIElements()
	{
		// Layout
		m_menuLayout = tgui::VerticalLayout::create();
		m_menuLayout->setSize("30%", "45d%");
		m_menuLayout->setOrigin(0.5f, 0.0f);
		m_menuLayout->setPosition("50%", "20%");

		// New game button
		m_newGameButton = tgui::Button::create("(gameOver) New Game");

		// Back to menu button
		m_backToMenuButton = tgui::Button::create("Back to menu");

		// callbacks
		m_newGameButton->onClick(&GameOverMenuComponent::NewGameButtonCallback, this);
		m_backToMenuButton->onClick(&GameOverMenuComponent::BackToMenuButtonCallback, this);

		// add to gui
		m_menuLayout->add(m_newGameButton);
		m_menuLayout->add(m_backToMenuButton);

		m_group->add(m_menuLayout);

	}


	void GameOverMenuComponent::UIShown()
	{
		IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
	}

	void GameOverMenuComponent::UIHidden()
	{
		IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
	}


	void GameOverMenuComponent::HandleSwitchToMainMenu()
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
	}

	void GameOverMenuComponent::NewGameButtonCallback()
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
	}

	void GameOverMenuComponent::BackToMenuButtonCallback()
	{
		HandleSwitchToMainMenu();
	}

	void GameOverMenuComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
	{
		HandleSwitchToMainMenu();
	}

}