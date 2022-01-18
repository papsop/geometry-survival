#pragma once
#include "../LoggerLevel.h"

namespace Engine
{
    class IBackendStrategy
    {
    public:
        IBackendStrategy() = default;
        virtual ~IBackendStrategy() = default;

        virtual void WriteText(LOGGER_LEVEL level, const char* source, const char* text) = 0;
    };
}