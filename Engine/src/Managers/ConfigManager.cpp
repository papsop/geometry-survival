#include "ConfigManager.h"
#include "../Application.h"

namespace Engine
{
    ConfigManager& ConfigManager::Get()
    {
        return Application::Instance().GetConfigManager();
    }
}