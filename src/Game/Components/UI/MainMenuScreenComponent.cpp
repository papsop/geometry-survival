#include "MainMenuScreenComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/ViewManager.h>
#include "../../Managers/GameManager.h"
#include "Controllers/MainMenuUIControllerComponent.h"

#include <Engine/ImGui/imgui.h>

namespace Game
{

  MainMenuScreenComponent::MainMenuScreenComponent(Engine::GameObject& obj)
    : IImGuiComponent(obj)
  {}

  // Button callbacks
  void MainMenuScreenComponent::PlayButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RestartGamePlay();
  }

	void MainMenuScreenComponent::SettingsButtonCallback()
	{
		auto* parentController = Owner.GetComponent<MainMenuUIControllerComponent>();
		if (parentController)
		{
			parentController->SetState(MainMenuUIControllerComponent::MainMenuUIStates::SETTINGS);
		}
	}

	void MainMenuScreenComponent::QuitButtonCallback()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->QuitGame();
  }

	void MainMenuScreenComponent::Update(float dt)
	{
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.5f, work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		if (ImGui::Begin("Main menu", NULL, window_flags))
		{
			ImGui::Text("Main menu\n");
			if (ImGui::Button("Play", ImVec2(300.0f, 100.f)))
			{
				PlayButtonCallback();
			}
			if (ImGui::Button("Settings", ImVec2(300.0f, 100.f)))
			{
				SettingsButtonCallback();
			}
      if (ImGui::Button("Quit", ImVec2(300.0f, 100.f)))
      {
        QuitButtonCallback();
      }
		}
		ImGui::End();

		//// timeline test

  //  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always, ImVec2(0.f, 0.f));
		//ImGui::SetNextWindowSize(ImVec2(500.0f, 200.0f));
  //  ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

		//if (ImGui::Begin("timeline", NULL, window_flags))
		//{
		//	ImGui::BeginTimeline("timeline_test", 200.0f);

		//	float times[2] = { 50.0f, 100.0f };
		//	ImGui::TimelineEvent("event1", times);

		//	ImGui::EndTimeline();
		//}
		//ImGui::End();
	}
}