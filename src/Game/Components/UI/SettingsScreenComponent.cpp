#include "SettingsScreenComponent.h"
#include <Engine/Application.h>
#include <Engine/ImGui/imgui.h>
#include "../../Managers/GameManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include "Controllers/MainMenuUIControllerComponent.h"
namespace Game
{

	SettingsScreenComponent::SettingsScreenComponent(Engine::GameObject& obj)
		: IImGuiComponent(obj)
	{
		m_resolutions = Engine::RenderManager::Get().GetResolutionEntries();
	}

  void SettingsScreenComponent::VirtualOnActivated()
  {
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
		Engine::RenderManager::Get().OnSettingsChanged.AddListener(this, &SettingsScreenComponent::OnSettingsChanged);
		OnSettingsChanged(); // Set initial values
  }

  void SettingsScreenComponent::VirtualOnDeactivated()
  {
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
		Engine::RenderManager::Get().OnSettingsChanged.RemoveListener(this);
  }

  void SettingsScreenComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    BackToMenuCallback();
  }

  // Callbacks
	void SettingsScreenComponent::SaveSettingsCallback()
	{
    Engine::RenderManagerSettings settings;
    settings.Fullscreen = m_fullscreenVal;
		settings.ResolutionEntry = m_resolutions[m_selectedResolution];
		Engine::RenderManager::Get().SetSettings(settings);
	}

	void SettingsScreenComponent::OnSettingsChanged()
	{
		auto settings = Engine::RenderManager::Get().GetSettings();
		m_fullscreenVal = settings.Fullscreen;
		m_currentResolutionEntry = settings.ResolutionEntry;
		
		for (int i=0;i<m_resolutions.size();i++)
		{
			if (m_resolutions[i].Name == m_currentResolutionEntry.Name)
			{
				m_selectedResolution = i;
				break;
			}
		}
	}

	void SettingsScreenComponent::Update(float dt)
	{
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.5f, work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoDocking;

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
				ImGui::End();
				SaveSettingsCallback();
				return;
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