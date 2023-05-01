#include "IngameHUDComponent.h"

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
		if (m_weaponComponent)
		{
			ImGui::Separator();

			if (m_weaponComponent->IsReloading())
			{
				ImGui::Text("Ammo: RELOADING");
				ImGui::ProgressBar(m_weaponComponent->GetReloadCompletion());
			}
			else
			{
				ImGui::Text("Ammo: %d/%d", m_weaponComponent->GetAmmo(), m_weaponComponent->GetMaxAmmo());
			}
			
		}
		ImGui::End();

		if (m_rpgComponent)
		{
			InitializeOverlayWindow("PlayerHealthBar", { 0.5f, 0.55f }, { 0.05f, 0.05f }, true, {0.5f, 0.5f});
			ImGui::ProgressBar(m_rpgComponent->GetStat(RPGStats::CURRENT_HEALTH)/ m_rpgComponent->GetStat(RPGStats::MAX_HEALTH));
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