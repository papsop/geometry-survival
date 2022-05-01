#include "Application.h"
#include "Managers/InputManager.h"
#include "Core/GameObject.h"
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

    Application::Application()
        : m_assetsManager(std::unique_ptr<AssetsManager>(new AssetsManager()))
        , m_subsystemManager(std::unique_ptr<SubsystemManager>(new SubsystemManager()))
        , m_inputManager(std::unique_ptr<InputManager>(new InputManager()))
        , m_gameObjectManager(std::unique_ptr<GameObjectManager>(new GameObjectManager()))
        , m_sceneManager(std::unique_ptr<SceneManager>(new SceneManager()))
    {
        // Passing unique_ptr like this, so we can keep private manager constructors
        // and link Application as friend class (won't work with make_unique)
    }

    void Application::HandleViewEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            Stop();
            break;
        default:
            m_inputManager->HandleWindowEvent(event);
            break;
        }
    }

    void Application::Run(ApplicationInjection& injection)
    {
        LOG_DEBUG("Starting Application");
        LOG_DEBUG("Loading Config");
        m_config = m_assetsManager->LoadEngineConfig();
        LOG_DEBUG("Config loaded");
        // Let game create it's subsystems
        injection.RegisterGameComponents(*this);

        //Scene scene;
        //auto debugID = scene.AddGameObjectViaFactory(DebugGOFactory());
        //auto playerID = scene.AddGameObjectViaFactory(PlayerFactory());
        //auto enemyID = scene.AddGameObjectViaFactory(SeekingEnemyFactory());

        // Create and set ViewStrategy
        GetSubsystemManager().m_view->SetViewStrategy(
            new view::WindowViewStrategy( std::bind(&Application::HandleViewEvent, this, std::placeholders::_1) )
        );
        m_inputManager->SetViewSubsystem(GetSubsystemManager().GetViewSubsystemPointer());

        // Let the game initialize scene/gameobjects/etc.
        injection.BeforeGameLoop(*this);

        // Start updating
        sf::Clock clock;
        while (m_applicationIsRunning)
        {
            sf::Time elapsed = clock.restart();
            float lastFrameMS = elapsed.asSeconds();
            
            m_subsystemManager->GetViewSubsystem().PollEvents();
			// debug exit
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Stop();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) m_sceneManager->SaveAllScenes();
            // Update managers
            m_inputManager->Update();
            m_sceneManager->Update(lastFrameMS);    // update scene's state machine
           
            m_subsystemManager->Update(lastFrameMS);

            // reset input for this frame
            m_inputManager->PostUpdate();
            m_gameObjectManager->CleanupGameObjects();
        }
        LOG_DEBUG("----------------------------- Stopping Application, time to destroy");
        // clear backends when application.run() ends
        // if we wait for destructor - IDebuggable will 
        // try to unregister from subsystem that doesn't exist anymore
        Logger::Instance().ClearBackends();
    }

	void Application::Stop()
	{
        m_applicationIsRunning = false;
		E_ApplicationStopped eventData;

		DispatchEvent(eventData);
	}

};