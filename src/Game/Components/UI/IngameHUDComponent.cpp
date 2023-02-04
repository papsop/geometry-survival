#include "IngameHUDComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/Application.h>
namespace Game
{

	IngameHUDComponent::IngameHUDComponent(Engine::GameObject& obj)
		: IUIComponent(obj)
		, m_gameTimer(Engine::Application::Instance().GetGameManager<GameManager>()->GetGameTimer())
	{
		m_gameTimer.Reset();
	}

	void IngameHUDComponent::RegisterUIElements()
	{

		m_levelLabel = tgui::Label::create("0");
		m_levelLabel->setOrigin(0.5f, 0.5f);
		m_levelLabel->setPosition("50%", "10%");
		m_levelLabel->setTextSize(48);
		m_group->add(m_levelLabel);

		m_experienceBar = tgui::Panel::create();
		m_experienceBar->setOrigin(0.0f, 0.0f);
		m_experienceBar->setPosition(0, 5);
		m_experienceBar->setSize("100%", "20");
		m_group->add(m_experienceBar);

		m_ammoLabel = tgui::Label::create("0/0");
		m_ammoLabel->setOrigin(1.0f, 1.0f);
		m_ammoLabel->setPosition("100%", "100%");
		m_ammoLabel->setTextSize(48);
		m_group->add(m_ammoLabel);

		m_timerLabel = tgui::Label::create("00:00");
		m_timerLabel->setOrigin(1.0f, 0.5f);
		m_timerLabel->setPosition("100%", "10%");
		m_timerLabel->setTextSize(48);
		m_group->add(m_timerLabel);

		m_healthLabel = tgui::Label::create("<3 0/0");
		m_healthLabel->setOrigin(0.0f, 0.5f);
		m_healthLabel->setPosition("0%", "10%");
		m_healthLabel->setTextSize(48);
		m_group->add(m_healthLabel);
	}

	void IngameHUDComponent::UIShown()
	{
		IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
		IEventListener<event::E_PlayerLeveledUp>::RegisterListener();
		IEventListener<event::E_PlayerDied>::RegisterListener();
	}

	void IngameHUDComponent::UIHidden()
	{
		IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		IEventListener<event::E_PlayerLeveledUp>::UnregisterListener();
		IEventListener<event::E_PlayerDied>::UnregisterListener();
	}

	void IngameHUDComponent::Update(float dt)
	{
		m_gameTimer.Update(dt);

		m_timerLabel->setText(tgui::String(m_gameTimer.GetTimerAsString()));

		if (m_levelComponent)
		{
			m_levelLabel->setText(tgui::String(m_levelComponent->GetCurrentLevel()));

			tgui::String levelProgress = tgui::String(m_levelComponent->GetCurrentLevelProgress() * 100) + "%";
			m_experienceBar->setSize(levelProgress, m_experienceBar->getSize().y);
		}

		if (m_weaponComponent)
		{
			tgui::String ammoString = tgui::String(m_weaponComponent->GetCurrentAmmo()) + "/" + tgui::String(m_weaponComponent->GetMaxAmmo());
			m_ammoLabel->setText(ammoString);
		}

		if (m_rpgComponent)
		{
			tgui::String healthString = tgui::String("<3 " + std::to_string(static_cast<int>(m_rpgComponent->GetStat(RPGStats::CURRENT_HEALTH))) + "/" + std::to_string(static_cast<int>(m_rpgComponent->GetStat(RPGStats::MAX_HEALTH))));
			m_healthLabel->setText(healthString);
		}

	}

	void IngameHUDComponent::ResetPlayerComponents(Engine::GameObject* player)
	{
		if (player)
		{
			m_levelComponent = player->GetComponent<LevelComponent>();
			m_weaponComponent = player->GetComponent<WeaponComponent>();
			m_rpgComponent = player->GetComponent<RPGComponent>();
		}
		else
		{
			m_levelComponent = nullptr;
			m_weaponComponent = nullptr;
			m_rpgComponent = nullptr;
		}
	}

	void IngameHUDComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
	{
		auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
		if (parentController)
		{
			parentController->SetState(IngameUIControllerComponent::IngameUIState::MENU);
		}
	}

	void IngameHUDComponent::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData)
	{
		ResetPlayerComponents(eventData.PlayerObject);
	}

	void IngameHUDComponent::ReceiveEvent(const event::E_PlayerLeveledUp& eventData)
	{
		auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
		if (parentController)
		{
			parentController->SetState(IngameUIControllerComponent::IngameUIState::SKILL_PICKER);
		}
	}

	void IngameHUDComponent::ReceiveEvent(const event::E_PlayerDied& eventData)
	{
		auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
		if (parentController)
		{
			parentController->SetState(IngameUIControllerComponent::IngameUIState::GAMEOVER);
		}
	}

}