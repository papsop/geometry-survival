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

        RenderManager* GetRenderManager() { return m_renderManager.get(); };
        InputManager* GetInputManager() { return m_inputManager.get(); };

    private:
        SingletonManager() = default;
        ~SingletonManager() = default;
        void Init(Application& app);


        std::unique_ptr<RenderManager> m_renderManager;
        std::unique_ptr<InputManager> m_inputManager;

        //RenderManager *m_renderManager = nullptr;
        //InputManager *m_inputManager = nullptr;

    friend class Application; // only Application should be able to Init this manager
    };
};

