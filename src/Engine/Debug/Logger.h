#pragma once
#include "LoggerLevel.h"
#include "Backend/IBackendStrategy.h"
#include <memory>
#include <vector>

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
        ~Logger() = default;
        static Logger& Instance();

        void Log(LOGGER_LEVEL level, const char* source, const char* format, ...);

        void AddBackend(std::unique_ptr<IBackendStrategy> backend);
        void ClearBackends();

        void SetLevel(LOGGER_LEVEL level) { m_levelFilter = level; }
    private:
        Logger();
        // config file?
        LOGGER_LEVEL m_levelFilter = LOGGER_LEVEL::DEBUG;

        std::vector< std::unique_ptr<IBackendStrategy> > m_backends;
    };
};


