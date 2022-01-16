#pragma once

#define LOG_INFO(...) Engine::Logger::Instance().Log(Engine::Logger::LEVEL::INFO, __func__, ##__VA_ARGS__)
#define LOG_WARN(...) Engine::Logger::Instance().Log(Engine::Logger::LEVEL::WARN, __func__, ##__VA_ARGS__)
#define LOG_ERROR(...) Engine::Logger::Instance().Log(Engine::Logger::LEVEL::ERROR, __func__, ##__VA_ARGS__)

#define DD_ASSERT(exp, ...) if(!(exp)) { LOG_ERROR(__VA_ARGS__); abort();}

namespace Engine
{
    class Logger
    {
    public:
        enum class LEVEL
        {
            INFO = 0,
            WARN = 1,
            ERROR = 2
        };

        static Logger& Instance();

        void Log(LEVEL level, const char* source, const char* format, ...);

    private:
        Logger();
        ~Logger() = default;

        // config file?
        LEVEL m_levelFilter = LEVEL::INFO;
    };
};


