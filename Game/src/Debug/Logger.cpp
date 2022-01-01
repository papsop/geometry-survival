#include "Logger.h"

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

namespace Game
{
    Logger::Logger()
    {
        Log(LEVEL::INFO, "Created Logger");
    }

    Logger& Logger::Instance()
    {
        static Logger instance;
        return instance;
    }

    // TODO: actually filter levels
    bool Logger::Log(LEVEL level, const char* format, ...)
    {
        // format va arguments
        char log_message[1024];
        va_list arg;
        va_start(arg, format);
        vsprintf_s(log_message, format, arg);
        va_end(arg);

        // print colored log
        if (level == LEVEL::INFO)
        {
            printf(ANSI_COLOR_CYAN "[INFO] %s\n" ANSI_COLOR_RESET, log_message);
        }
        else if (level == LEVEL::WARN)
        {
            printf(ANSI_COLOR_YELLOW "[WARN] %s\n" ANSI_COLOR_RESET, log_message);
        }
        else if (level == LEVEL::ERROR)
        {
            printf(ANSI_COLOR_RED "[ERROR] %s\n" ANSI_COLOR_RESET, log_message);
        }
        return true;
    }
};
