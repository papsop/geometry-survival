#include "SingletonManager.h"


namespace Game
{
    SingletonManager& SingletonManager::Instance()
    {
        static SingletonManager instance;
        return instance;
    }

    void SingletonManager::Init(Application& app)
    {
        if (m_renderManager.get() == nullptr && m_inputManager.get() == nullptr)
        {
            m_renderManager = std::make_unique<RenderManager>(app);
            m_inputManager = std::make_unique<InputManager>(app);
        }
        else
        {
            // error already initialized
        }
    }
};