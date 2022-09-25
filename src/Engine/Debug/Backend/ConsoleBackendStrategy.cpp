#include "ConsoleBackendStrategy.h"
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
  void ConsoleBackendStrategy::WriteText(LOGGER_LEVEL level, const char* source, const char* text)
  {
    if (level == LOGGER_LEVEL::DEBUG)
    {
      printf(ANSI_COLOR_GREEN "[DEBUG-%s] %s\n" ANSI_COLOR_RESET, source, text);
    }
    else if (level == LOGGER_LEVEL::INFO)
    {
      printf(ANSI_COLOR_CYAN "[INFO-%s] %s\n" ANSI_COLOR_RESET, source, text);
    }
    else if (level == LOGGER_LEVEL::WARN)
    {
      printf(ANSI_COLOR_YELLOW "[WARN-%s] %s\n" ANSI_COLOR_RESET, source, text);
    }
    else if (level == LOGGER_LEVEL::ERROR)
    {
      printf(ANSI_COLOR_RED "[ERROR-%s] %s\n" ANSI_COLOR_RESET, source, text);
    }
  }
};