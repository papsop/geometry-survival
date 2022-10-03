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

  Engine::InputManager& Application::GetInputManager()
  {
    GET_MANAGER_HELPER("SubsystemManager", *m_inputManager);
  }

  Engine::GameObjectManager& Application::GetGameObjectManager()
  {
    GET_MANAGER_HELPER("GameObjectManager", *m_gameObjectManager);
  }

  Engine::SceneManager& Application::GetSceneManager()
  {
    GET_MANAGER_HELPER("SceneManager", *m_sceneManager);
  }

  Engine::PhysicsManager& Application::GetPhysicsManager()
  {
    GET_MANAGER_HELPER("PhysicsManager", *m_physicsManager);
  }

  Engine::ViewManager& Application::GetViewManager()
  {
    GET_MANAGER_HELPER("ViewManager", *m_viewManager);
  }

  Engine::ComponentManager& Application::GetComponentManager()
  {
    GET_MANAGER_HELPER("ComponentManager", *m_componentManager);
  }

  Engine::ConfigManager& Application::GetConfigManager()
  {
    GET_MANAGER_HELPER("ConfigManager", *m_configManager);
  }

  Engine::UIManager& Application::GetUIManager()
  {
    GET_MANAGER_HELPER("UIManager", *m_uiManager);
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
    // Update
		m_sceneManager->Update(dt);
		m_componentManager->Update(dt);
    m_physicsManager->Update(dt);

    m_timeAccumulator += dt;
    // FixedUpdate
    while (m_timeAccumulator >= m_fixedUpdate)
    {
      m_physicsManager->FixedUpdate(m_fixedUpdate);
      m_sceneManager->FixedUpdate(m_fixedUpdate);
      m_componentManager->FixedUpdate(m_fixedUpdate);
      m_timeAccumulator -= m_fixedUpdate;
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
    m_uiManager->OnInit();
    m_viewManager->OnInit();
    m_physicsManager->OnInit();
	  m_inputManager->OnInit();
	  m_sceneManager->OnInit();
    m_componentManager->OnInit();
    m_gameObjectManager->OnInit();
    LOG_INFO("Initializing complete");
    // Let the game create it's subsystems
    //injection.RegisterGameComponents(*this);

    m_fixedUpdate = m_physicsManager->GetFixedUpdate();

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
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Stop();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) m_configManager->StoreModifiedCvars();

      // Update managers
      m_inputManager->Update();

      // Process GameObject messages
      m_gameObjectManager->Update(lastFrameMS);
      // Update custom managers that the game registered
      // These managers actually update Components etc. as they see fit
      for (auto&& managerEntry : m_managers)
      {
          managerEntry.second->Update(lastFrameMS);
      }

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
    m_configManager->OnDestroy();
    LOG_INFO("Destroying complete");
  }

	void Application::Stop()
	{
    m_applicationIsRunning = false;
    EventManager::Get().DispatchEvent(event::E_ApplicationStopped());
	}

};