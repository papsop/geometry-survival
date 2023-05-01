#pragma once
#include "IBackendStrategy.h"
#include "../../Debug/IDebuggable.h"
#include "../../Core/Events.h"
#include "../../Core/EventData.h"

namespace Engine
{

	struct LogEntry
	{
		LOGGER_LEVEL Level;
		std::string Value;
	};

	class ImGuiBackendStrategy : public IBackendStrategy, public IDebuggable,
		public IEventListener<event::E_WindowClosed>, 
		public IEventListener<event::E_OnConsoleKeyAction>
	{
	public:
		ImGuiBackendStrategy();
		~ImGuiBackendStrategy() override;

		void WriteText(LOGGER_LEVEL level, const char* source, const char* text) override;
		void Clear();

		void Debug(Engine::VisualDebugContext& debugContext) override;

	protected:
		void ReceiveEvent(const event::E_WindowClosed& eventData) override;
		void ReceiveEvent(const event::E_OnConsoleKeyAction& eventData) override;

	private:
		bool m_shouldShowConsole;
		int m_maxLevel;
		std::vector<LogEntry> m_entries;

	};
};


