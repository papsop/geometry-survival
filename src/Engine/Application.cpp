#include "Application.h"
#include "Managers/InputManager.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Serializing/SceneSerializer.h"

#include "View/WindowViewStrategy.h"
#include "View/ConsoleViewStrategy.h"

#include "Debug/Logger.h"
#include "Debug/Backend/WindowBackendStrategy.h"

#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <functional>

namespace Engine
{

    Application* Application::m_instance = nullptr;

    Application::Application()
    {
        DD_ASSERT(m_instance == nullptr, "Only one Application instance allowed");
        m_instance = this;
    }

    void Application::HandleViewEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            Stop();
            break;
        default:
            m_inputManager.HandleWindowEvent(event);
            break;
        }
    }
	void Application::DestroyRegisteredManager()
	{
//         while (!m_managers.empty())
//         {
//             auto& m = std::move(m_managers.front());
//             m->OnDestroy();
//             m_gameManagers.pop();
//         }
	}

	void Application::Run(ApplicationInjection& injection)
    {
        LOG_DEBUG("Starting Application");
        LOG_DEBUG("Initializing managers");
        m_configManager.OnInit();
        m_configManager.LoadCvarsFromFile();
        m_physicsManager.OnInit();
        m_viewManager.OnInit();
		m_inputManager.OnInit();
		m_sceneManager.OnInit();
        m_componentManager.OnInit();
        m_gameObjectManager.OnInit();
        LOG_DEBUG("Initializing complete");
        // Let game create it's subsystems
        injection.RegisterGameComponents(*this);

        //Scene scene;
        //auto debugID = scene.AddGameObjectViaFactory(DebugGOFactory());
        //auto playerID = scene.AddGameObjectViaFactory(PlayerFactory());
        //auto enemyID = scene.AddGameObjectViaFactory(SeekingEnemyFactory());

        // Create and set ViewStrategy
		m_viewManager.SetViewStrategy(
			new view::WindowViewStrategy(std::bind(&Application::HandleViewEvent, this, std::placeholders::_1))
		);
        // Let the game initialize scene/gameobjects/etc.
        injection.BeforeGameLoop(*this);

        // Start updating
        sf::Clock clock;
        while (m_applicationIsRunning)
        {
            sf::Time elapsed = clock.restart();
            float lastFrameMS = elapsed.asSeconds();
            
            m_viewManager.PollEvents();
			// debug exit
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Stop();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) {
                m_configManager.GetCvar("spawner_radius")->SetValueFloat(60.0f);
                m_configManager.GetCvar("spawner_cooldown")->SetValueFloat(0.5f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) m_configManager.StoreModifiedCvars();
            // Update managers
            m_inputManager.Update();
            m_physicsManager.Update(lastFrameMS);
            m_sceneManager.Update(lastFrameMS);  
           
            m_viewManager.Update(lastFrameMS);
            m_componentManager.Update(lastFrameMS);

            // reset input for this frame
            m_inputManager.PostUpdate();
            m_gameObjectManager.CleanupGameObjects();
        }

        m_configManager.StoreModifiedCvars();
        LOG_DEBUG("Destroying managers");
        DestroyRegisteredManager();
        m_gameObjectManager.OnDestroy();
        m_componentManager.OnDestroy();
        m_sceneManager.OnDestroy();
        m_inputManager.OnDestroy();
        m_physicsManager.OnDestroy();
        m_viewManager.OnDestroy();
        m_configManager.OnDestroy();
		LOG_DEBUG("Destroying complete");
    }

	void Application::Stop()
	{
        m_applicationIsRunning = false;
        EventManager::Get().DispatchEvent(E_ApplicationStopped());
	}

};