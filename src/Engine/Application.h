#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Core/Config.h"
#include "Core/ApplicationInjection.h"
#include "Managers/AllManagers.h"

#define GET_MANAGER_HELPER(name, var) {                                                 \
                                           DD_ASSERT(((var).IsInitialized()), (name)); \
                                           return (var);                                \
                                      }

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

        const Config& GetConfig() { return m_config; }

        InputManager& GetInputManager() { GET_MANAGER_HELPER("SubsystemManager", m_inputManager); };
        EventManager& GetEventManager() { GET_MANAGER_HELPER("EventManager", m_eventManager); };
        GameObjectManager& GetGameObjectManager() { GET_MANAGER_HELPER("GameObjectManager", m_gameObjectManager); };
        SceneManager& GetSceneManager() { GET_MANAGER_HELPER("SceneManager", m_sceneManager); };
        PhysicsManager& GetPhysicsManager() { GET_MANAGER_HELPER("PhysicsManager", m_physicsManager); };
        ViewManager& GetRenderManager() { GET_MANAGER_HELPER("ViewManager", m_viewManager); };
        ComponentManager& GetComponentManager() { GET_MANAGER_HELPER("ComponentManager", m_componentManager); };

        void Run(ApplicationInjection& injection);
        bool IsRunning() const { return m_applicationIsRunning;  }
        void Stop();
    private:
        Application();
        ~Application() = default;
        Config m_config;

        bool m_applicationIsRunning = true;
        
        void HandleViewEvent(const sf::Event& event);

        EventManager m_eventManager;
        InputManager m_inputManager;
        GameObjectManager m_gameObjectManager;
        SceneManager m_sceneManager;
        PhysicsManager m_physicsManager;
        ViewManager m_viewManager;
        ComponentManager m_componentManager;
    };
};


