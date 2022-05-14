#pragma once
#include "IBackendStrategy.h"
#include "../IDebuggable.h"
#include "../../Core/Events.h"
#include <string>
#include <vector>

namespace Engine 
{
    class WindowBackendStrategy : public IBackendStrategy, public IEventListener<E_WindowClosed>, public IDebuggableComponent
    {
    public:
        WindowBackendStrategy() = default;
        ~WindowBackendStrategy() override = default;

        void WriteText(LOGGER_LEVEL level, const char* source, const char* text) override;
        void Debug(view::IViewStrategy* viewStrategy) override;

        void ReceiveEvent(const E_WindowClosed& eventData) override;
    private:
        struct DebugEntry
        {
            sf::Color Color;
            std::string Text;
        };

        std::vector<DebugEntry> m_entries;

        size_t m_maxLinesConsole = 10;
        bool m_shouldShowConsole = false;
        bool m_pressedLastFrame = false;
    };
}


