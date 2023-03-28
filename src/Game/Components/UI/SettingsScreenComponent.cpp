#include "SettingsScreenComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/ViewManager.h>
#include <Engine/ImGui/imgui.h>
#include "../../Managers/GameManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include "Controllers/MainMenuUIControllerComponent.h"
namespace Game
{

	SettingsScreenComponent::SettingsScreenComponent(Engine::GameObject& obj)
		: IImGuiComponent(obj)
	{
		m_resolutions.emplace_back(Engine::ResolutionEntry("1920x1080", { 1920, 1080 }));
		m_resolutions.emplace_back(Engine::ResolutionEntry("1280x720",  { 1280, 720  }));
		m_resolutions.emplace_back(Engine::ResolutionEntry("1024x576",  { 1024, 576  }));
	}

  void SettingsScreenComponent::VirtualOnActivated()
  {
    Engine::ViewManager::Get().RegisterComponent(this);
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
  }

  void SettingsScreenComponent::VirtualOnDeactivated()
  {
    Engine::ViewManager::Get().UnregisterComponent(this);
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
  }

  void SettingsScreenComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    BackToMenuCallback();
  }

  // Callbacks
	void SettingsScreenComponent::SaveSettingsCallback()
	{
    Engine::ViewManagerSettings settings;
    settings.Fullscreen = m_fullscreenVal;
		settings.ResolutionEntry = m_resolutions[m_selectedResolution];
    Engine::ViewManager::Get().SetSettings(settings);
	}

	void SettingsScreenComponent::Update(float dt)
	{
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.5f, work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		if (ImGui::Begin("Settings", NULL, window_flags))
		{
			ImGuiComboFlags flags = 0;
			const char* comboPreview = m_resolutions[m_selectedResolution].Name;
			if (ImGui::BeginCombo("Resolution", comboPreview, flags))
			{
				for (int i = 0; i < m_resolutions.size(); i++)
				{
					const bool isSelected = m_selectedResolution == i;
					if (ImGui::Selectable(m_resolutions[i].Name, isSelected))
						m_selectedResolution = i;

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

      ImGui::Checkbox("Fullscreen", &m_fullscreenVal); 

			ImGui::Separator();
			if (ImGui::Button("Save", ImVec2(200.0f, 100.f)))
			{
				SaveSettingsCallback();
			}
      ImGui::SameLine();
			if (ImGui::Button("Back to menu", ImVec2(200.0f, 100.f)))
			{
				BackToMenuCallback();
			}
		}
		ImGui::End();
	}

	void SettingsScreenComponent::BackToMenuCallback()
  {
    auto* ingameController = Owner.GetComponent<IngameUIControllerComponent>();
    if (ingameController)
    {
      ingameController->SetState(IngameUIControllerComponent::IngameUIState::MENU);
      return;
    }

		auto* mainMenuController = Owner.GetComponent<MainMenuUIControllerComponent>();
		if (mainMenuController)
		{
      mainMenuController->SetState(MainMenuUIControllerComponent::MainMenuUIStates::MENU);
      return;
		}

  }
}