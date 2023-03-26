#include "WindowBackendStrategy.h"
#include "../Logger.h"
#include "../../Utils/VectorUtils.h"
#include "../../Components/Core.h"
#include "../../View/Renderables.h"
#include "../../Managers/InputManager.h"

#include <iostream>
#include "../../ImGui/imgui.h"
namespace Engine
{

	WindowBackendStrategy::WindowBackendStrategy()
	{
		IEventListener<event::E_WindowClosed>::RegisterListener();
	}

	WindowBackendStrategy::~WindowBackendStrategy()
	{
		IEventListener<event::E_WindowClosed>::UnregisterListener();
	}

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

		if (ImGui::Begin("Logger", &m_shouldShowConsole))
		{
			if (ImGui::BeginPopup("Options"))
			{
				ImGui::Button("Clear");
				ImGui::EndPopup();
			}
			ImGui::End();
		}
	}

	void WindowBackendStrategy::ReceiveEvent(const event::E_WindowClosed& eventData)
	{
		Logger::Instance().UnregisterBackend(this);
	}

};