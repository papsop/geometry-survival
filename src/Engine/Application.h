#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Core/ApplicationInjection.h"
#include "Managers/AllManagers.h"

namespace Engine
{

    class Application : public IEventDispatcher<E_ApplicationStopped>
    {
    public:
        static Application& Instance()
        {
            static Application instance;
            return instance;
        }

        InputManager& GetInputManager() { return *m_inputManager; }
        GameObjectManager& GetGameObjectManager() { return *m_gameObjectManager; }
        SubsystemManager& GetSubsystemManager() { return *m_subsystemManager; }
        SceneManager& GetSceneManager() { return *m_sceneManager; }

        void Run(ApplicationInjection& injection);
        bool IsRunning() const { return m_applicationIsRunning;  }
        void Stop();
    private:
        Application();
        ~Application() = default;

        bool m_applicationIsRunning = true;

        void HandleViewEvent(const sf::Event& event);

        // Order is important because of destructions
        std::unique_ptr<DatabaseManager> m_databaseManager;             // first, because other managers might need it already initialized
        std::unique_ptr<SubsystemManager> m_subsystemManager;
        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<GameObjectManager> m_gameObjectManager;
        std::unique_ptr<SceneManager> m_sceneManager;
    };
};


