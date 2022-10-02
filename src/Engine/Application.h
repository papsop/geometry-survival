#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "Core/ApplicationInjection.h"
#include "Managers/AllManagers.h"
#include "Core/Events.h"

#define GET_MANAGER_HELPER(name, var) {                                                                 \
                                           DD_ASSERT((var).IsInitialized(), name " not initialized");   \
                                           return (var);                                                \
                                      }

namespace Engine
{

    class Application : public IEventListener<event::E_SFMLEvent>
    {
    public:
        Application();
        ~Application() = default;
        static Application& Instance()
        {
            DD_ASSERT(m_instance != nullptr, "Application not created");
            return *m_instance;
        }
        
        // Engine managers
        InputManager& GetInputManager() { GET_MANAGER_HELPER("SubsystemManager", m_inputManager); };
        GameObjectManager& GetGameObjectManager() { GET_MANAGER_HELPER("GameObjectManager", m_gameObjectManager); };
        SceneManager& GetSceneManager() { GET_MANAGER_HELPER("SceneManager", m_sceneManager); };
        PhysicsManager& GetPhysicsManager() { GET_MANAGER_HELPER("PhysicsManager", m_physicsManager); };
        ViewManager& GetViewManager() { GET_MANAGER_HELPER("ViewManager", m_viewManager); };
        ComponentManager& GetComponentManager() { GET_MANAGER_HELPER("ComponentManager", m_componentManager); };
        ConfigManager& GetConfigManager() { GET_MANAGER_HELPER("ConfigManager", m_configManager); };
        UIManager& GetUIManager() { GET_MANAGER_HELPER("UIManager", m_uiManager); };

        // Game managers
        template<typename T,
                typename ... Args,
                typename = std::enable_if_t<std::is_base_of<IManager, T>::value>
                >
        void RegisterGameManager(Args&& ... args);

        template<typename T,
          typename = std::enable_if_t<std::is_base_of<IManager, T>::value>
        >
          T* GetGameManager();
        void DestroyRegisteredManagers();

        void Run(ApplicationInjection& injection);
        bool IsRunning() const { return m_applicationIsRunning;  }
        void Stop();

        void UpdateGameplay(float dt);
    protected:
        void ReceiveEvent(const event::E_SFMLEvent& eventData) override;
    private:
        static Application* m_instance;

        bool m_applicationIsRunning = true;
       
        InputManager m_inputManager;
        GameObjectManager m_gameObjectManager;
        SceneManager m_sceneManager;
        PhysicsManager m_physicsManager;
        ViewManager m_viewManager;
        ComponentManager m_componentManager;
        ConfigManager m_configManager;
        UIManager m_uiManager;

        std::map< uint32_t, std::unique_ptr<IManager> > m_managers;

        float m_timeAccumulator = 0.0f;
        float m_fixedUpdate = -1.0f;
    };

};

#include "Application.inl"
