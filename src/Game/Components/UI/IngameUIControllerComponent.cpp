#include "IngameUIControllerComponent.h"
#include "IngameHUDComponent.h"
#include "IngameMenuComponent.h"
#include "SettingsScreenComponent.h"
#include "SkillPickerScreenComponent.h"

namespace Game
{

  IngameUIControllerComponent::IngameUIControllerComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {

  }

  void IngameUIControllerComponent::VirtualOnActivated()
  {
    m_components[0] = Owner.GetComponent<IngameHUDComponent>();
    m_components[1] = Owner.GetComponent<SkillPickerScreenComponent>();
    m_components[2] = Owner.GetComponent<IngameMenuComponent>();
    m_components[3] = Owner.GetComponent<SettingsScreenComponent>();
    m_components[4] = nullptr;

    SetState(IngameUIState::HUD);
  }

  void IngameUIControllerComponent::SetState(IngameUIState newState)
  {
    LOG_WARN("Swapping ingameUIController state, new: %d", static_cast<size_t>(newState));

    for (auto& c : m_components)
    {
      if (c)
      {
        c->Deactivate();
      }
      
    }
    m_currentState = newState;
    m_components[static_cast<size_t>(newState)]->Activate();
  }

}