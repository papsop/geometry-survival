#include "SkillPickerScreenComponent.h"
#include <Engine/Application.h>

#include "../../Skills/Skill_AmmoStealer.h"
#include "../../Skills/Skill_AmmoPiercer.h"
#include "../../Skills/Skill_BulletDamage.h"
#include "../../Managers/GameManager.h"
#include "../../Managers/SkillsManager.h"

#include "Controllers/IngameUIControllerComponent.h"
#include <Engine/ImGui/imgui.h>

namespace Game
{

  SkillPickerScreenComponent::SkillPickerScreenComponent(Engine::GameObject& obj)
    : IImGuiComponent(obj)
  {

  }

	void SkillPickerScreenComponent::VirtualOnActivated()
	{
		GameManager::Get()->SetGameState(GameState::Paused);
		m_skillsToPick = Engine::Application::Instance().GetGameManager<SkillsManager>()->GetNRandomSkills(3);
	}

	void SkillPickerScreenComponent::VirtualOnDeactivated()
	{
		GameManager::Get()->SetGameState(GameState::Gameplay);
	}

  void SkillPickerScreenComponent::Update(float dt)
  {
		// Center window
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.5f, work_size.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

    if (ImGui::Begin("Skill picker", NULL, window_flags))
    {
      ImGui::Text("Choose a skill");
      ImGui::Separator();
      for (int i = 0; i < m_skillsToPick.size(); i++)
      {
        ImGui::BeginGroup();
        ImGui::PushItemWidth(150.0f);
        if (ImGui::Button(m_skillsToPick[i]->GetSkillName(), ImVec2(150.0f, 100.0f)))
        {
          PickSkillNumber(i);
        }
        ImGui::Text(m_skillsToPick[i]->GetSkillDescription());
        ImGui::EndGroup();
        ImGui::SameLine();
      }
    }
    ImGui::End();
  }

	void SkillPickerScreenComponent::ReturnToGame()
  {
    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::HUD);
    }
  }

  void SkillPickerScreenComponent::PickSkillNumber(size_t index)
  {
    if (index < m_numberOfSkills)
    {
      auto* player = Engine::Application::Instance().GetGameManager<GameManager>()->GetPlayerGameObject();
      LOG_WARN("Chosen skill index '%d'", index);
      m_skillsToPick[index]->Learn(player);
      ReturnToGame();
    }
  }

}