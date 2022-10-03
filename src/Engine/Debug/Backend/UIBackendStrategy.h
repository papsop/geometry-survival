#pragma once
#include "IBackendStrategy.h"
#include "../IDebuggable.h"
#include "../../Core/Events.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/InputManager.h"
#include <string>
#include <vector>

namespace Engine
{
  class UIBackendStrategy : public IBackendStrategy, public IEventListener<event::E_WindowClosed>, public IEventListener<event::E_OnConsoleKeyAction>
  {
  public:
    UIBackendStrategy();
    ~UIBackendStrategy() override;

    void WriteText(LOGGER_LEVEL level, const char* source, const char* text) override;

  protected:
    void ReceiveEvent(const event::E_WindowClosed& eventData) override;
    void ReceiveEvent(const event::E_OnConsoleKeyAction& eventData) override;

  private:
    tgui::TextArea::Ptr m_textArea;
    bool m_shouldShowConsole = false;
  };
}


