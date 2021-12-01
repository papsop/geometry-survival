#pragma once
#include "RenderManager.h"
#include "InputManager.h"

#include "../Application.h"
#include <memory>

namespace Game
{
    class SingletonManager
    {
    public:
        static SingletonManager& Instance();

        const auto GetRenderManager() { return m_renderManager; };
        const auto GetInputManager() { return m_inputManager; };

    private:
        void Init(Application& app);

        std::shared_ptr<RenderManager> m_renderManager;
        std::shared_ptr<InputManager> m_inputManager;

    friend class Application; // only Application should be able to Init this manager
    };
};

