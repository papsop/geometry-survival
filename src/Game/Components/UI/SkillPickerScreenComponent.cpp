#include "SkillPickerScreenComponent.h"
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
#include "IngameUIControllerComponent.h"
namespace Game
{

  SkillPickerScreenComponent::SkillPickerScreenComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {

  }

  void SkillPickerScreenComponent::UIShown()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->SetGameState(GameManager::GameState::Paused);
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
      m_skillButtons[i] = tgui::Button::create(tgui::String(i));
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
      LOG_WARN("Chosen skill index '%d'", index);
      ReturnToGame();
    }
  }

}