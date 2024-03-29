#include "IngameMenuComponent.h"
#include <Engine/Managers/EventManager.h>
#include <Engine/Application.h>
#include <Engine/ImGui/imgui.h>

#include "../../Managers/GameManager.h"
#include "../../Core/EventData.h"
#include "Controllers/IngameUIControllerComponent.h"

namespace Game
{

  IngameMenuComponent::IngameMenuComponent(Engine::GameObject& obj)
    : IImGuiComponent(obj)
  {

  }
	void IngameMenuComponent::VirtualOnActivated()
	{
		GameManager::Get()->SetGameState(GameState::Paused);
		IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
	}

	void IngameMenuComponent::VirtualOnDeactivated()
	{
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
	}

	void IngameMenuComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::HUD);
      GameManager::Get()->SetGameState(GameState::Gameplay);
    } 
  }

  // ============= Button callbacks =============
  void IngameMenuComponent::NewGameButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

  void IngameMenuComponent::SettingsButtonCallback()
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::SETTINGS);
    }
  }

  void IngameMenuComponent::BackToMenuButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
  }

  void IngameMenuComponent::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }

	void IngameMenuComponent::Update(float dt)
	{
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 work_pos = viewport->WorkPos;
		ImGui::SetNextWindowPos(ImVec2(work_pos.x + work_size.x * 0.5f, work_pos.y + work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

		if (ImGui::Begin("Main menu", NULL, m_staticUIFlags))
		{
			ImGui::Text("Main menu\n");
			if (ImGui::Button("New Game", ImVec2(300.0f, 100.f)))
			{
				NewGameButtonCallback();
			}
			if (ImGui::Button("Settings", ImVec2(300.0f, 100.f)))
			{
				SettingsButtonCallback();
			}
			if (ImGui::Button("Back to menu", ImVec2(300.0f, 100.f)))
			{
				BackToMenuButtonCallback();
			}
			if (ImGui::Button("Quit game", ImVec2(300.0f, 100.f)))
			{
				QuitButtonCallback();
			}
		}
		ImGui::End();
	}
}