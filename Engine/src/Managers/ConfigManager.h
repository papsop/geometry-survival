#pragma once

#include <map>

namespace Engine
{
    class Application;
    class ConfigManager
    {
    public:
        ConfigManager() = default;
        ~ConfigManager() = default;

        static ConfigManager& Get();
    };
}


