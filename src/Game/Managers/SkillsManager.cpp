#include "SkillsManager.h"

#include "../Skills/Skill_AmmoPiercer.h"
#include "../Skills/Skill_AmmoStealer.h"
#include "../Skills/Skill_BulletDamage.h"
#include "../Skills/Skill_PickupRadius.h"
#include "../Skills/Skill_BurningAmmo.h"
#include "GameManager.h"

#include <cstdlib>
#include <time.h>

namespace Game
{

  SkillsManager::SkillsManager(Engine::Application& app)
    : m_app(app)
  {

  }

  void SkillsManager::VirtualOnInit()
  {
    std::srand((unsigned)time(NULL));
    ResetToDefaultSkills();

    DebuggableOnInit();
  }

	void SkillsManager::VirtualOnDestroy()
	{
		DebuggableOnDestroy();
	}

	void SkillsManager::ResetToDefaultSkills()
  {
    m_availableSkills.clear();
    m_availableSkills.push_back(std::make_unique<Skill_AmmoPiercer>());
    m_availableSkills.push_back(std::make_unique<Skill_AmmoStealer>());
    m_availableSkills.push_back(std::make_unique<Skill_BulletDamage>());
    m_availableSkills.push_back(std::make_unique<Skill_PickupRadius>());
    m_availableSkills.push_back(std::make_unique<Skill_BurningAmmo>());
  }

  std::vector< ISkill* > SkillsManager::GetNRandomSkills(int N)
  {
    DD_ASSERT(N < m_availableSkills.size(), "Trying to retrieve more skills than available");

    for (int i = m_availableSkills.size() -1 ; i > 0; i--)
    {
      int index = std::rand() % (i+1);
      std::swap(m_availableSkills[i], m_availableSkills[index]);
    }

    std::vector< ISkill* > result;
    for (int i = 0; i < N; i++)
    {
      result.push_back(m_availableSkills[i].get());
    }
    return result;
  }

	void SkillsManager::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(0.0f, work_size.y-70.0f), ImGuiCond_Once, ImVec2(0.0f, 1.0f));
		ImGui::SetNextWindowBgAlpha(0.1f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

		if (ImGui::Begin("SkillsManager", NULL, window_flags))
		{
			ImGuiComboFlags flags = 0;
			const char* comboPreview = m_availableSkills[m_selectedSkill]->GetSkillName();
			if (ImGui::BeginCombo("Skill", comboPreview, flags))
			{
				for (int i = 0; i < m_availableSkills.size(); i++)
				{
					const bool isSelected = m_selectedSkill == i;
					if (ImGui::Selectable(m_availableSkills[i]->GetSkillName(), isSelected))
						m_selectedSkill = i;

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
      ImGui::SameLine();
      auto* player = Engine::Application::Instance().GetGameManager<GameManager>()->GetPlayerGameObject();

      //ImGui::BeginDisabled(!player); // button disabled if there isn't a player registered yet
      if (player && ImGui::Button("Learn"))
      {
				m_availableSkills[m_selectedSkill]->Learn(player);
      }
      //ImGui::EndDisabled();
		}
		ImGui::End();
	}

}