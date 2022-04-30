#pragma once
#include "../Core/Config.h"

namespace Engine
{
    class AssetsManager
    {
    public:
        static AssetsManager& Get();
		
        Config LoadEngineConfig();
    private:
        AssetsManager() = default;
        
        // specific file names
        const char* m_configFileName = "assets/config.yaml";

    friend class Application;   // only Application can create a manager
    };
}
