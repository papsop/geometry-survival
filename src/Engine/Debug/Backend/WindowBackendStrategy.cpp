#include "WindowBackendStrategy.h"
#include "../Logger.h"
#include "../../Utils/VectorUtils.h"
#include "../../Components/Core.h"
#include "../../View/Renderables.h"
#include "../../Managers/InputManager.h"

#include <iostream>

namespace Engine
{
    void WindowBackendStrategy::WriteText(LOGGER_LEVEL level, const char* source, const char* text)
    {
        DebugEntry entry;
        entry.Text = "" + std::string(source) + " - " + std::string(text);

        if (level == LOGGER_LEVEL::DEBUG)
            entry.Color = sf::Color::Green;
        else if (level == LOGGER_LEVEL::INFO)
            entry.Color = sf::Color::Cyan;
        else if (level == LOGGER_LEVEL::WARN)
            entry.Color = sf::Color::Yellow;
        else if (level == LOGGER_LEVEL::ERROR)
            entry.Color = sf::Color::Red;

        m_entries.emplace_back(entry);
    }

	void WindowBackendStrategy::Debug(view::IViewStrategy* viewStrategy)
	{
		if (InputManager::Get().GetAction(InputManager::Action::ShowConsole).PressedThisFrame)
			m_shouldShowConsole = !m_shouldShowConsole;

		if (m_shouldShowConsole)
		{
// 			size_t bottomBound = (m_entries.size() > m_maxLinesConsole) ? (m_entries.size() - m_maxLinesConsole) : 0;
// 			for (size_t i = bottomBound; i < m_entries.size(); ++i)
// 			{
// 				Transform t;
// 				t.Position = math::Vec2(5.0f, 13.0f * (i - bottomBound));
// 				view::Text text(&t);
// 				text.Size = 9;
// 				text.Color = m_entries[i].Color;
// 				text.Value = m_entries[i].Text;
// 				text.UseScreenPosition = true;
// 				viewStrategy->Render(text);
// 			}
		}
	}

	void WindowBackendStrategy::ReceiveEvent(const event::E_WindowClosed& eventData)
	{
		Logger::Instance().UnregisterBackend(this);
	}

};