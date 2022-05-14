#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Core/Config.h"
#include "Core/ApplicationInjection.h"
#include "Managers/AllManagers.h"

#define GET_MANAGER_HELPER(name, var) {                                                                 \
                                           DD_ASSERT((var).IsInitialized(), name " not initialized");   \
                                           return (var);                                                \
                                      }

namespace Engine
{

    class Application : public IEventDispatcher<E_ApplicationStopped>
    {
    public:
        Application();
        ~Application() = default;
        static Application& Instance()
        {
            DD_ASSERT(m_instance != nullptr, "Application not created");
            return *m_instance;
        }

        const Config& GetConfig() { return m_config; }

        InputManager& GetInputManager() { GET_MANAGER_HELPER("SubsystemManager", m_inputManager); };
        GameObjectManager& GetGameObjectManager() { GET_MANAGER_HELPER("GameObjectManager", m_gameObjectManager); };
        SceneManager& GetSceneManager() { GET_MANAGER_HELPER("SceneManager", m_sceneManager); };
        PhysicsManager& GetPhysicsManager() { GET_MANAGER_HELPER("PhysicsManager", m_physicsManager); };
        ViewManager& GetViewManager() { GET_MANAGER_HELPER("ViewManager", m_viewManager); };
        ComponentManager& GetComponentManager() { GET_MANAGER_HELPER("ComponentManager", m_componentManager); };
        SerializationManager& GetSerializationManager() { GET_MANAGER_HELPER("SerializationManager", m_serializationManager); };

        void Run(ApplicationInjection& injection);
        bool IsRunning() const { return m_applicationIsRunning;  }
        void Stop();
    private:
        Config m_config;

        static Application* m_instance;

        bool m_applicationIsRunning = true;
        
        void HandleViewEvent(const sf::Event& event);

        InputManager m_inputManager;
        GameObjectManager m_gameObjectManager;
        SceneManager m_sceneManager;
        PhysicsManager m_physicsManager;
        ViewManager m_viewManager;
        ComponentManager m_componentManager;
        SerializationManager m_serializationManager;
    };
};


