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

  void UIManager::SetSFMLWindow(sf::RenderWindow& window)
  {
    // always reset, because just using ->setWindow() crashes
    m_gui = std::make_unique<tgui::Gui>(window);
    EventManager::Get().DispatchEvent(event::E_GUIReset());
  }

  void UIManager::DrawGui()
  {
    if (m_gui)
      m_gui->draw();
  }

  tgui::Gui* UIManager::GetGui()
  { // caller is responsible for checking if gui is valid
    return m_gui.get();
  }

  void UIManager::ReceiveEvent(const event::E_SFMLEvent& eventData)
  {
    if (m_gui)
      m_gui->handleEvent(eventData.Event);
  }
}