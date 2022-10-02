#include "UIBackendStrategy.h"

namespace Engine
{

  UIBackendStrategy::UIBackendStrategy()
  {
    auto* gui = UIManager::Get().GetGui();
    if (gui)
    {
      m_textArea = tgui::TextArea::create();
      m_textArea->setSize("100%", "30%");
      m_textArea->setReadOnly(true);
      m_textArea->setVisible(m_shouldShowConsole);

      gui->add(m_textArea);
    }
  }

  UIBackendStrategy::~UIBackendStrategy()
  {
    auto* gui = UIManager::Get().GetGui();
    if (gui)
    {
      gui->remove(m_textArea);
    }
  }

  void UIBackendStrategy::WriteText(LOGGER_LEVEL level, const char* source, const char* text)
  {
    if (m_textArea)
    {
      tgui::String value = text;
      value += "\n";
      m_textArea->addText(value);
    }
  }

  void UIBackendStrategy::ReceiveEvent(const event::E_WindowClosed& eventData)
  {
    Logger::Instance().UnregisterBackend(this);
  }

  void UIBackendStrategy::ReceiveEvent(const InputManager::E_InputActionEvent& eventData)
  {
    if (eventData.Action != InputManager::Action::ShowConsole)
      return;

    if (eventData.ActionEntry.PressedThisFrame && !m_shouldShowConsole)
    {
      m_shouldShowConsole = true; 
    }
    else if (eventData.ActionEntry.PressedThisFrame && m_shouldShowConsole)
    {
      m_shouldShowConsole = false;
    }

    m_textArea->setVisible(m_shouldShowConsole);
    m_textArea->moveToFront();
  }

}