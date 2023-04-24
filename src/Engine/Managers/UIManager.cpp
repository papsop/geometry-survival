#include "UIManager.h"
#include "../Application.h"

#include "EventManager.h"
#include "../Core/EventData.h"

namespace Engine
{

  UIManager& UIManager::Get()
  {
    return Application::Instance().GetUIManager();
  }

  void UIManager::VirtualOnInit()
  {
    IEventListener<event::E_SFMLEvent>::RegisterListener();
  }

  void UIManager::VirtualOnDestroy()
  {
    IEventListener<event::E_SFMLEvent>::UnregisterListener();
  }

  void UIManager::DrawGui()
  {
  }

  void UIManager::ReceiveEvent(const event::E_SFMLEvent& eventData)
  {
  }
}