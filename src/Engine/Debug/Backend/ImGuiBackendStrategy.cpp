#include "ImGuiBackendStrategy.h"
#include "../../Managers/InputManager.h"

#include "../../ImGui/imgui.h"
#include <sstream>

namespace Engine
{

	ImGuiBackendStrategy::ImGuiBackendStrategy()
	{
		DebuggableOnInit();
		IEventListener<event::E_WindowClosed>::RegisterListener();
		IEventListener<event::E_OnConsoleKeyAction>::RegisterListener();

		m_maxLevel = static_cast<unsigned int>(LOGGER_LEVEL::DEBUG);
		m_shouldShowConsole = false;
	}

	ImGuiBackendStrategy::~ImGuiBackendStrategy()
	{
		DebuggableOnDestroy();
		IEventListener<event::E_WindowClosed>::UnregisterListener();
		IEventListener<event::E_OnConsoleKeyAction>::UnregisterListener();
	}

	void ImGuiBackendStrategy::WriteText(LOGGER_LEVEL level, const char* source, const char* text)
	{
		LogEntry entry;
		std::stringstream ss;
		ss << "{"<< static_cast<int>(level) << "}" << "[" << source << "] " << text;
		entry.Value = ss.str();
		entry.Level = level;
		m_entries.emplace_back(entry);
	}

	void ImGuiBackendStrategy::Debug(VisualDebugContext& debugContext)
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		if (m_shouldShowConsole && ImGui::Begin("Logger", &m_shouldShowConsole))
		{
			if (ImGui::SmallButton("Clear"))
			{
				Clear();
			}
			ImGui::SameLine();

			ImGuiSliderFlags flags = ImGuiSliderFlags_None;
			ImGui::SliderInt("Logger level", &m_maxLevel, 0, 3, "%d");

			if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -1), false, ImGuiWindowFlags_HorizontalScrollbar))
			{
				for (int i = 0; i < m_entries.size(); i++)
				{
					auto level = static_cast<int>(m_entries[i].Level);
					if (level < m_maxLevel)
						continue;

					ImVec4 textColor;
					switch (level)
					{
					case 0:
						textColor = {.3f, .3f, .3f, 1.f};
						break;
					case 1:
						textColor = { .0f, .0f, 1.f, 1.f };
						break;
					case 2:
						textColor = { 1.f, 1.f, .0f, 1.f };
						break;
					case 3:
						textColor = { 1.f, .0f, .0f, 1.f };
						break;
					default:
						textColor = { 1.f, 1.f, 1.f, 1.f };
						break;
					}

					ImGui::PushStyleColor(ImGuiCol_Text, textColor);
					ImGui::TextUnformatted(m_entries[i].Value.c_str());
					ImGui::PopStyleColor();
				}
			}

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

			ImGui::EndChild();
			ImGui::End();
		}

	}

	void ImGuiBackendStrategy::Clear()
	{
		m_entries.clear();
	}

	void ImGuiBackendStrategy::ReceiveEvent(const event::E_WindowClosed& eventData)
	{
		Logger::Instance().UnregisterBackend(this);
	}

	void ImGuiBackendStrategy::ReceiveEvent(const event::E_OnConsoleKeyAction & eventData)
	{
		m_shouldShowConsole = !m_shouldShowConsole;
	}

}