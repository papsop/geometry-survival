#include "SkillPickerScreenComponent.h"
#include <Engine/Application.h>

#include "../../Skills/Skill_AmmoStealer.h"
#include "../../Skills/Skill_AmmoPiercer.h"
#include "../../Managers/GameManager.h"
#include "IngameUIControllerComponent.h"
#include <TGUI/String.hpp>
namespace Game
{

  SkillPickerScreenComponent::SkillPickerScreenComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {

  }

  void SkillPickerScreenComponent::UIShown()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Paused);

    m_skillsToPick[0] = std::make_unique<Skill_AmmoStealer>();
    m_skillsToPick[1] = std::make_unique<Skill_AmmoPiercer>();
    m_skillsToPick[2] = std::make_unique<Skill_AmmoPiercer>();
    for (size_t i = 0; i < 3; i++)
    {
      // TODO: Skill description
      tgui::String skillLabel = tgui::String(m_skillsToPick[i]->GetSkillName());
      m_skillButtons[i]->setText(skillLabel);
    }
  }

  void SkillPickerScreenComponent::UIHidden()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Gameplay);
  }

  void SkillPickerScreenComponent::RegisterUIElements()
  {
    // Layout
    m_layout = tgui::HorizontalLayout::create();
    m_layout->setSize("50%", "30%");
    m_layout->setOrigin(0.5f, 0.0f);
    m_layout->setPosition("50%", "20%");

    // skill buttons
    for (size_t i = 0; i < 3; i++)
    {
      tgui::String skillLabel = tgui::String("EmptyPicker");
      //+tgui::String(m_skillsToPick[i]->GetSkillDescription());
      m_skillButtons[i] = tgui::Button::create(skillLabel);
      m_skillButtons[i]->setSize("20%", "20%");
      m_skillButtons[i]->onClick(&SkillPickerScreenComponent::PickSkillNumber, this, i);
      m_layout->add(m_skillButtons[i]);
    }

    m_experienceBar = tgui::Panel::create();
    m_experienceBar->setOrigin(0.0f, 0.0f);
    m_experienceBar->setPosition(0, 5);
    m_experienceBar->setSize("100%", "20");
    
    m_group->add(m_experienceBar);
    m_group->add(m_layout);
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