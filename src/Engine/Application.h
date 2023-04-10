#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "Core/ApplicationInjection.h"
#include "Core/Events.h"
#include "Debug/Logger.h"

namespace Engine
{
  class InputManager;
  class GameObjectManager;
  class SceneManager;
  class PhysicsManager;
  class ViewManager;
  class ComponentManager;
  class ConfigManager;
  class UIManager;
  class ResourceManager;

  class Application : public IEventListener<event::E_SFMLEvent>
  {
  public:
      Application();
      ~Application();
      static Application& Instance()
      {
          DD_ASSERT(m_instance != nullptr, "Application not created");
          return *m_instance;
      }
        
      // Engine managers
      InputManager& GetInputManager();
      GameObjectManager& GetGameObjectManager();
      SceneManager& GetSceneManager();
      PhysicsManager& GetPhysicsManager();
      ViewManager& GetViewManager();
      ComponentManager& GetComponentManager();
      ConfigManager& GetConfigManager();
      UIManager& GetUIManager();
      ResourceManager& GetResourceManager();

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
       
      void CreateManagers();

      std::unique_ptr<InputManager> m_inputManager;
      std::unique_ptr<GameObjectManager> m_gameObjectManager;
      std::unique_ptr<SceneManager> m_sceneManager;
      std::unique_ptr<PhysicsManager> m_physicsManager;
      std::unique_ptr<ViewManager> m_viewManager;
      std::unique_ptr<ComponentManager> m_componentManager;
      std::unique_ptr<ConfigManager> m_configManager;
			std::unique_ptr<UIManager> m_uiManager;
			std::unique_ptr<ResourceManager> m_resourceManager;

      std::map< uint32_t, std::unique_ptr<IManager> > m_managers;

      float m_timeAccumulator = 0.0f;
  };

};

#include "Application.inl"
