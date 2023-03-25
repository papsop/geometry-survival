#include "IngameHUDComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/Application.h>
#include <Engine/ImGui/imgui.h>
#include <Engine/Managers/Viewmanager.h>
namespace Game
{

	IngameHUDComponent::IngameHUDComponent(Engine::GameObject& obj)
		: IImGuiComponent(obj)
		, m_gameTimer(Engine::Application::Instance().GetGameManager<GameManager>()->GetGameTimer())
	{
		m_gameTimer.Reset();
	}

	void IngameHUDComponent::Update(float dt)
	{
		m_gameTimer.Update(dt);

		//m_timerLabel->setText(tgui::String(m_gameTimer.GetTimerAsString()));

		if (m_weaponComponent && m_rpgComponent && m_levelComponent)
		{
			InitializeOverlayWindow("LevelOverlay", { 0.0f, 0.0f }, {1.0f, 0.1f}, true);
			ImGui::ProgressBar(m_levelComponent->GetCurrentLevelProgress());
			ImGui::End();

			InitializeOverlayWindow("HUDOverlay", { 0.0f, 0.1f }, {0.2f, 0.2f}, true);
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("Level: %d", m_levelComponent->GetCurrentLevel());
			ImGui::Separator();
			ImGui::Text("Health: %.0f/%.0f", m_rpgComponent->GetStat(RPGStats::CURRENT_HEALTH), m_rpgComponent->GetStat(RPGStats::MAX_HEALTH));
			ImGui::Separator();
			ImGui::Text("Ammo: %d/%d", m_weaponComponent->GetCurrentAmmo(), m_weaponComponent->GetMaxAmmo());
			ImGui::End();
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

	void IngameHUDComponent::VirtualOnActivated()
	{
		Engine::ViewManager::Get().RegisterComponent(this);
		IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
		IEventListener<event::E_PlayerLeveledUp>::RegisterListener();
		IEventListener<event::E_PlayerDied>::RegisterListener();
	}

	void IngameHUDComponent::VirtualOnDeactivated()
	{
		Engine::ViewManager::Get().UnregisterComponent(this);
		IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		IEventListener<event::E_PlayerLeveledUp>::UnregisterListener();
		IEventListener<event::E_PlayerDied>::UnregisterListener();
	}

}