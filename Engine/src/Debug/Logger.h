#pragma once
#include "LoggerLevel.h"
#include <memory>

#define LOG_INFO(...) Engine::Logger::Instance().Log(Engine::LOGGER_LEVEL::INFO, __func__, ##__VA_ARGS__)
#define LOG_WARN(...) Engine::Logger::Instance().Log(Engine::LOGGER_LEVEL::WARN, __func__, ##__VA_ARGS__)
#define LOG_ERROR(...) Engine::Logger::Instance().Log(Engine::LOGGER_LEVEL::ERROR, __func__, ##__VA_ARGS__)

#define DD_ASSERT(exp, ...) if(!(exp)) { LOG_ERROR(__VA_ARGS__); abort();}

namespace Engine
{
    class Logger
    {
    public:
        static Logger& Instance();

        void Log(LOGGER_LEVEL level, const char* source, const char* format, ...);
    private:
        Logger();
        ~Logger() = default;

        // config file?
        LOGGER_LEVEL m_levelFilter = LOGGER_LEVEL::INFO;
    };
};


