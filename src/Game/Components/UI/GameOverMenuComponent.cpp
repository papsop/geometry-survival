#include "GameOverMenuComponent.h"
#include "../../Managers/GameManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/Application.h>
#include <Engine/ImGui/imgui.h>

namespace Game
{

	GameOverMenuComponent::GameOverMenuComponent(Engine::GameObject& obj)
		: IImGuiComponent(obj)
	{

	}

	void GameOverMenuComponent::VirtualOnActivated()
	{
		Engine::IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
	}

	void GameOverMenuComponent::VirtualOnDeactivated()
	{
		Engine::IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
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

	void GameOverMenuComponent::Update(float dt)
	{
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.5f, work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoDocking;

		if (ImGui::Begin("Main menu", NULL, window_flags))
		{
			ImGui::Text("GameOver\n");
			if (ImGui::Button("New game", ImVec2(300.0f, 100.f)))
			{
				NewGameButtonCallback();
			}
			if (ImGui::Button("Back to menu", ImVec2(300.0f, 100.f)))
			{
				BackToMenuButtonCallback();
			}
		}
		ImGui::End();
	}

	void GameOverMenuComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
	{
		HandleSwitchToMainMenu();
	}

}