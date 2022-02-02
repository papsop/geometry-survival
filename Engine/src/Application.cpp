#include "Application.h"
#include "Managers/InputManager.h"
#include "Core/GameObject.h"
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
        : m_databaseManager(std::unique_ptr<DatabaseManager>(new DatabaseManager()))
        , m_subsystemManager(std::unique_ptr<SubsystemManager>(new SubsystemManager()))
        , m_inputManager(std::unique_ptr<InputManager>(new InputManager()))
        , m_entityManager(std::unique_ptr<EntityManager>(new EntityManager()))
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
            m_applicationIsRunning = false;
            break;
        default:
            m_inputManager->HandleWindowEvent(event);
            break;
        }
    }

    void Application::Run(ApplicationInjection& injection)
    {
        LOG_DEBUG("Starting Application");

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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) SceneManager::Get().SetActiveScene(0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) SceneManager::Get().SetActiveScene(1);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) SceneManager::Get().LoadSceneAdditively(1);

            sf::Time elapsed = clock.restart();
            float lastFrameMS = elapsed.asSeconds();
            
            m_subsystemManager->GetViewSubsystem().PollEvents();

            m_inputManager->Update();

            // debug exit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
           
            m_subsystemManager->Update(lastFrameMS);

            // reset input for this frame
            m_inputManager->PostUpdate();
            m_entityManager->CleanupEntities();
//         
        }
        LOG_DEBUG("----------------------------- Stopping Application, time to destroy");
        Engine::Logger::Instance().ResetBackend();
    }
};