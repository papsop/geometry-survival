#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <functional>

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
	class ResourceManager;
	class RenderManager;
	class EditorManager;

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
      ComponentManager& GetComponentManager();
      ConfigManager& GetConfigManager();
			ResourceManager& GetResourceManager();
			RenderManager& GetRenderManager();
      EditorManager& GetEditorManager();

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

      void AddEndOfFrameDeferredAction(std::function<void()> func);
  protected:
      void ReceiveEvent(const event::E_SFMLEvent& eventData) override;
  private:
      static Application* m_instance;

      bool m_applicationIsRunning = true;
       
      void CreateManagers();
      void EndOfFrame();

      std::unique_ptr<InputManager> m_inputManager;
      std::unique_ptr<GameObjectManager> m_gameObjectManager;
      std::unique_ptr<SceneManager> m_sceneManager;
      std::unique_ptr<PhysicsManager> m_physicsManager;
      std::unique_ptr<ComponentManager> m_componentManager;
      std::unique_ptr<ConfigManager> m_configManager;
			std::unique_ptr<ResourceManager> m_resourceManager;
			std::unique_ptr<RenderManager> m_renderManager;
      std::unique_ptr<EditorManager> m_editorManager;

      std::map< uint32_t, std::unique_ptr<IManager> > m_managers;
      std::vector< std::function<void()> > m_endOfFrameDeferredActions;

      float m_timeAccumulator = 0.0f;
  };

};

#include "Application.inl"
