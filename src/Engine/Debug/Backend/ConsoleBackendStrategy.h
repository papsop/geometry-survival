#pragma once
#include "IBackendStrategy.h"

namespace Engine
{
  class ConsoleBackendStrategy : public IBackendStrategy
  {
  public:
    ConsoleBackendStrategy() = default;
    ~ConsoleBackendStrategy() override = default;

    void WriteText(LOGGER_LEVEL level, const char* source, const char* text) override;
  };
};


