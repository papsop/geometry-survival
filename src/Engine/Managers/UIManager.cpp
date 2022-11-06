#include "UIManager.h"
#include "../Application.h"

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
    if (!m_gui)
    {
      m_gui = std::make_unique<tgui::Gui>(window);
    }
    else
    {
      m_gui->setWindow(window);
    }
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