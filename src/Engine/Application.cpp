#include "Application.h"
#include "Managers/InputManager.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Serializing/SceneSerializer.h"

#include "View/WindowViewStrategy.h"
#include "View/ConsoleViewStrategy.h"

#include "Debug/Logger.h"
#include "Debug/Backend/WindowBackendStrategy.h"

#include "Managers/ComponentManager.h"
#include "Managers/InputManager.h"
#include "Managers/ConfigManager.h"
#include "Managers/EventManager.h"
#include "Managers/SceneManager.h"
#include "Managers/PhysicsManager.h"
#include "Managers/UIManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/ResourceManager.h"

#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <functional>

#define GET_MANAGER_HELPER(name, var) {                                                              \
                                        DD_ASSERT((var).IsInitialized(), name " not initialized");   \
                                        return (var);                                                \
                                      }

#define CREATE_MANAGER(class, var) {                                            \
                                    var = std::unique_ptr<class>(new class()); \
                                   }

namespace Engine
{
  // ===========================================================
  // Get singletons
  // ===========================================================

  InputManager& Application::GetInputManager()
  {
    GET_MANAGER_HELPER("SubsystemManager", *m_inputManager);
  }

  GameObjectManager& Application::GetGameObjectManager()
  {
    GET_MANAGER_HELPER("GameObjectManager", *m_gameObjectManager);
  }

  SceneManager& Application::GetSceneManager()
  {
    GET_MANAGER_HELPER("SceneManager", *m_sceneManager);
  }

  PhysicsManager& Application::GetPhysicsManager()
  {
    GET_MANAGER_HELPER("PhysicsManager", *m_physicsManager);
  }

  ViewManager& Application::GetViewManager()
  {
    GET_MANAGER_HELPER("ViewManager", *m_viewManager);
  }

  ComponentManager& Application::GetComponentManager()
  {
    GET_MANAGER_HELPER("ComponentManager", *m_componentManager);
  }

  ConfigManager& Application::GetConfigManager()
  {
    GET_MANAGER_HELPER("ConfigManager", *m_configManager);
  }

	UIManager& Application::GetUIManager()
	{
		GET_MANAGER_HELPER("UIManager", *m_uiManager);
  }

	ResourceManager& Application::GetResourceManager()
	{
		GET_MANAGER_HELPER("ResourceManager", *m_resourceManager);
	}

	// ===========================================================
  // Application stuff
  // ===========================================================
  Application* Application::m_instance = nullptr;

  Application::Application()
  {
    DD_ASSERT(m_instance == nullptr, "Only one Application instance allowed");
    m_instance = this;
  }

	Application::~Application()
	{
   /* empty and must be here, the unique_ptr's destructor is unknown if THIS destructor is in the header file
   * - https://stackoverflow.com/a/34073093/1953344
   */
	}

	void Application::CreateManagers()
  {
    CREATE_MANAGER(InputManager, m_inputManager);
    CREATE_MANAGER(GameObjectManager, m_gameObjectManager);
    CREATE_MANAGER(SceneManager, m_sceneManager);
    CREATE_MANAGER(PhysicsManager, m_physicsManager);
    CREATE_MANAGER(ViewManager, m_viewManager);
    CREATE_MANAGER(ComponentManager, m_componentManager);
    CREATE_MANAGER(ConfigManager, m_configManager);
		CREATE_MANAGER(UIManager, m_uiManager);
		CREATE_MANAGER(ResourceManager, m_resourceManager);
  }

  void Application::ReceiveEvent(const event::E_SFMLEvent& eventData)
  {
    if (eventData.Type == sf::Event::Closed)
      Stop();
  }

	void Application::DestroyRegisteredManagers()
	{
    for (auto it = m_managers.cbegin(); it != m_managers.cend(); /* no increment */)
    {
      it->second->OnDestroy();
      m_managers.erase(it++);
    }
	}

	void Application::UpdateGameplay(float dt)
	{
    auto fixedUpdate = m_physicsManager->GetFixedUpdate();
    // Update
		m_sceneManager->Update(dt);
		m_componentManager->Update(dt);
    m_physicsManager->Update(dt);

		m_timeAccumulator += dt;
    // FixedUpdate
    while (m_timeAccumulator >= fixedUpdate)
    {
      m_physicsManager->FixedUpdate(fixedUpdate);
      m_sceneManager->FixedUpdate(fixedUpdate);
      m_componentManager->FixedUpdate(fixedUpdate);
      m_timeAccumulator -= fixedUpdate;

      if (m_timeAccumulator > 0 && m_timeAccumulator < fixedUpdate)
      {
				m_physicsManager->FixedUpdate(m_timeAccumulator);
				m_sceneManager->FixedUpdate(m_timeAccumulator);
				m_componentManager->FixedUpdate(m_timeAccumulator);
        m_timeAccumulator = 0;
      }
    }

	}

  void Application::Run(ApplicationInjection& injection)
  {
    LOG_INFO("Starting Application");
    LOG_INFO("Creating managers");
    CreateManagers();
    LOG_INFO("Initializing managers");
    m_configManager->OnInit();
		m_configManager->LoadCvarsFromFile();
		m_resourceManager->OnInit();
		m_uiManager->OnInit();
    m_viewManager->OnInit();
    m_physicsManager->OnInit();
	  m_inputManager->OnInit();
	  m_sceneManager->OnInit();
    m_componentManager->OnInit();
    m_gameObjectManager->OnInit();
    LOG_INFO("Initializing complete");
    IEventListener<event::E_SFMLEvent>::RegisterListener();
    // Let the game create it's subsystems
    //injection.RegisterGameComponents(*this);

    // Create and set ViewStrategy
	  m_viewManager->SetViewStrategy(new view::WindowViewStrategy(*m_viewManager));
    // Let the game initialize scene/gameobjects/etc.
    injection.BeforeGameLoop(*this);

    // Start updating
    sf::Clock clock;

    while (m_applicationIsRunning)
    {
      sf::Time elapsed = clock.restart();
      float lastFrameMS = elapsed.asSeconds();

      m_viewManager->PollEvents();
	    // debug exit
	    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Stop();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) m_configManager->StoreModifiedCvars();

      // Update managers
      m_inputManager->Update();
      // Process GameObject messages
      m_gameObjectManager->Update(lastFrameMS);
      // Update custom managers that the game registered
      for (auto&& managerEntry : m_managers)
      {
          managerEntry.second->Update(lastFrameMS);
      }

      // Update components
      UpdateGameplay(lastFrameMS);

      // Rendering
      m_viewManager->Update(lastFrameMS);
      // reset input for this frame
      m_inputManager->PostUpdate();
      m_gameObjectManager->CleanupGameObjects();
    }

    //m_configManager.StoreModifiedCvars();
    LOG_INFO("Destroying managers");
    DestroyRegisteredManagers();
    m_gameObjectManager->OnDestroy();
    m_componentManager->OnDestroy();
    m_sceneManager->OnDestroy();
    m_inputManager->OnDestroy();
    m_physicsManager->OnDestroy();
    m_viewManager->OnDestroy();
    m_uiManager->OnDestroy();
		m_resourceManager->OnDestroy();
    m_configManager->OnDestroy();
    LOG_INFO("Destroying complete");
  }

	void Application::Stop()
	{
    m_applicationIsRunning = false;
    EventManager::Get().DispatchEvent(event::E_ApplicationStopped());
	}

};