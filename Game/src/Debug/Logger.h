#pragma once

#define LOG_INFO(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::INFO, __func__, ##__VA_ARGS__)
#define LOG_WARN(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::WARN, __func__, ##__VA_ARGS__)
#define LOG_ERROR(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::ERROR, __func__, ##__VA_ARGS__)

#define DD_ASSERT(exp, ...) if(!(exp)) { LOG_ERROR(__VA_ARGS__); abort();}

namespace Game
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


