#include "IngameUIComponent.h"
#include "../../Core/StateMachines/States/UI/GameHUDState.h"

namespace Game
{

  IngameUIComponent::IngameUIComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
  }

  void IngameUIComponent::OnCreate()
  {
    m_stateMachine.SetState(new GameHUDState());
  }

  void IngameUIComponent::OnDestroy()
  {

  }

  void IngameUIComponent::VirtualOnActivated()
  {

  }

  void IngameUIComponent::VirtualOnDeactivated()
  {

  }

  void IngameUIComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {

  }
}