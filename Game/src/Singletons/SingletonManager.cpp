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
        m_renderManager = std::make_shared<RenderManager>(app);
        m_inputManager = std::make_shared<InputManager>(app);
    }
};