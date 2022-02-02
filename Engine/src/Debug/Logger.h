#pragma once
#include "LoggerLevel.h"
#include "Backend/IBackendStrategy.h"
#include <memory>

#define LOG_DEBUG(...) Engine::Logger::Instance().Log(Engine::LOGGER_LEVEL::DEBUG, __func__, ##__VA_ARGS__)
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

        void SetBackend(std::unique_ptr<IBackendStrategy> backend);
        void ResetBackend();

        void SetLevel(LOGGER_LEVEL level) { m_levelFilter = level; }
    private:
        Logger();
        ~Logger() = default;

        // config file?
        LOGGER_LEVEL m_levelFilter = LOGGER_LEVEL::DEBUG;

        std::unique_ptr<IBackendStrategy> m_backend;
    };
};


