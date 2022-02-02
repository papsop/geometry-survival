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
        ResetBackend();
        Log(LOGGER_LEVEL::INFO, __func__, "Created Logger");
    }

    Logger& Logger::Instance()
    {
        static Logger instance;
        return instance;
    }

    void Logger::SetBackend(std::unique_ptr<IBackendStrategy> backend)
    {
        m_backend = std::move(backend);
    }

    void Logger::ResetBackend()
    {
        m_backend = std::make_unique<ConsoleBackendStrategy>();
    }

    void Logger::Log(LOGGER_LEVEL level, const char* source, const char* format, ...)
    {
        DD_ASSERT(m_backend != nullptr, "Logger backened not set");
        if (level < m_levelFilter) return;

        char log_message[1024];
        va_list arg;
        va_start(arg, format);
        vsprintf_s(log_message, format, arg);
        va_end(arg);

        m_backend->WriteText(level, source, log_message);
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
