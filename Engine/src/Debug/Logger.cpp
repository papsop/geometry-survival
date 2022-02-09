#include "Logger.h"
#include "Backend/ConsoleBackendStrategy.h"

#include <ctime>
#include <chrono>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#define ANSI_COLOR_RESET   "\x1b[0m"

namespace Engine
{
    Logger::Logger()
    {
    }

    Logger& Logger::Instance()
    {
        static Logger instance;
        return instance;
    }

    void Logger::AddBackend(std::unique_ptr<IBackendStrategy> backend)
    {
        m_backends.emplace_back(std::move(backend));
    }

    void Logger::ClearBackends()
    {
        m_backends.clear();
    }

    void Logger::Log(LOGGER_LEVEL level, const char* source, const char* format, ...)
    {
        if (m_backends.size() == 0) return;
        if (level < m_levelFilter) return;

        char log_message[1024];
        va_list arg;
        va_start(arg, format);
        vsprintf_s(log_message, format, arg);
        va_end(arg);

        for(auto&& backend : m_backends)
            backend->WriteText(level, source, log_message);

        // print colored log
        //if (level == LOGGER_LEVEL::INFO)
        //{
        //    printf(ANSI_COLOR_CYAN "[INFO-%s] %s\n" ANSI_COLOR_RESET, source, log_message);
        //}
        //else if (level == LOGGER_LEVEL::WARN)
        //{
        //    printf(ANSI_COLOR_YELLOW "[INFO-%s] %s\n" ANSI_COLOR_RESET, source, log_message);
        //}
        //else if (level == LOGGER_LEVEL::ERROR)
        //{
        //    printf(ANSI_COLOR_RED "[INFO-%s] %s\n" ANSI_COLOR_RESET, source, log_message);
        //}
    }
};
