#include "IngameHUDComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"

#include "IngameUIControllerComponent.h"

namespace Game
{

  IngameHUDComponent::IngameHUDComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {
  }

  void IngameHUDComponent::RegisterUIElements()
  {
    m_label = tgui::Label::create("Geometry survival");
    m_label->setOrigin(0.5f, 0.5f);
    m_label->setPosition("50%", "50%");
    m_label->setTextSize(48);

    m_group->add(m_label);
  }

  void IngameHUDComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    if (!IsActive()) return;

    auto* parentController = Owner.GetComponent<IngameUIControllerComponent>();
    if (parentController)
    {
      parentController->SetState(IngameUIControllerComponent::IngameUIState::MENU);
    }
  }

}