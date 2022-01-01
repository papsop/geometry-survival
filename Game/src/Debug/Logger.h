#pragma once

#define LOG_INFO(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::INFO, __VA_ARGS__)
#define LOG_WARN(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::WARN, __VA_ARGS__)
#define LOG_ERROR(...) Game::Logger::Instance().Log(Game::Logger::LEVEL::ERROR, __VA_ARGS__)

#define DD_ASSERT(exp, ...) if(!(exp)) { LOG_ERROR(__VA_ARGS__); abort();}

namespace Game
{
    class Logger
    {
    public:
        enum class LEVEL
        {
            INFO,
            WARN,
            ERROR
        };

        static Logger& Instance();

        bool Log(LEVEL level, const char* format, ...);
    private:
        Logger();
        ~Logger() = default;
    };
};


