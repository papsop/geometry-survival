#include "IngameHUDComponent.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/Application.h>
#include <Engine/ImGui/imgui.h>

namespace Game
{

	IngameHUDComponent::IngameHUDComponent(Engine::GameObject& obj)
		: IImGuiComponent(obj)
		, m_gameTimer(Engine::Application::Instance().GetGameManager<GameManager>()->GetGameTimer())
	{
		m_gameTimer.Reset();
	}

	void IngameHUDComponent::VirtualOnActivated()
	{
		IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
		IEventListener<event::E_PlayerLeveledUp>::RegisterListener();
		IEventListener<event::E_PlayerDied>::RegisterListener();
	}

	void IngameHUDComponent::VirtualOnDeactivated()
	{
		IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
		IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		IEventListener<event::E_PlayerLeveledUp>::UnregisterListener();
		IEventListener<event::E_PlayerDied>::UnregisterListener();
	}

	void IngameHUDComponent::Update(float dt)
	{
		m_gameTimer.Update(dt);
		if (m_levelComponent)
		{
			InitializeOverlayWindow("LevelOverlay", { 0.0f, 0.0f }, { 1.0f, 0.1f }, true);
			ImGui::ProgressBar(m_levelComponent->GetCurrentLevelProgress());
			ImGui::End();
		}

		InitializeOverlayWindow("HUDOverlay", { 0.0f, 0.1f }, { 0.2f, 0.2f }, true);

		if (m_levelComponent)
		{
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("Level: %d", m_levelComponent->GetCurrentLevel());
		}

		ImGui::End();

// 		if (m_weaponComponent)
// 		{
// 			InitializeOverlayWindow("Weapon bar", { 0.5f, 0.45f }, { 70.f, 70.f }, false, { 0.5f, 0.5f });
// 			ImGui::PushItemWidth(ImGui::GetWindowWidth());
// 			if (m_weaponComponent->IsReloading())
// 			{
// 				ImGui::ProgressBar(m_weaponComponent->GetReloadCompletion(), { 0.0f, 0.0f }, " ");
// 			}
// 			else
// 			{
// 				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("00/00").x) / 2.f);
// 				ImGui::Text("%02d/%02d", m_weaponComponent->GetAmmo(), m_weaponComponent->GetMaxAmmo());
// 			}
// 			ImGui::PopItemWidth();
// 			ImGui::End();
// 		}

		if (m_rpgComponent)
		{
      InitializeOverlayWindow("PlayerHealthBar", { 0.5f, 0.6f }, { 70.f, 70.f }, false, { 0.5f, 0.5f });
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, { 1.f, .0f, .0f, 1.f });
			ImGui::PushItemWidth(ImGui::GetWindowWidth());
      ImGui::ProgressBar(m_rpgComponent->GetStat(RPGStats::CURRENT_HEALTH) / m_rpgComponent->GetStat(RPGStats::MAX_HEALTH), {0.0f, 0.0f}, " ");
			ImGui::PopItemWidth();
			ImGui::PopStyleColor();
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

}