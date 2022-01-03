#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Managers/AllManagers.h"

#define PHYSICSSUBSYSTEM_REGISTER(c) Game::Application::Instance().GetSubsystemManager().m_physics->RegisterComponent((c));
#define PHYSICSSUBSYSTEM_UNREGISTER(c) Game::Application::Instance().GetSubsystemManager().m_physics->UnregisterComponent((c));
#define ACTORSUBSYSTEM_REGISTER(c) Game::Application::Instance().GetSubsystemManager().m_actor->RegisterComponent((c));
#define ACTORSUBSYSTEM_UNREGISTER(c) Game::Application::Instance().GetSubsystemManager().m_actor->UnregisterComponent((c));
#define VIEWSUBSYSTEM_REGISTER(c) Game::Application::Instance().GetSubsystemManager().m_view->RegisterComponent((c));
#define VIEWSUBSYSTEM_UNREGISTER(c) Game::Application::Instance().GetSubsystemManager().m_view->UnregisterComponent((c));

namespace Game
{

    class Application
    {
    public:
        static Application& Instance()
        {
            static Application instance;
            return instance;
        }

        InputManager& GetInputManager() { return *m_inputManager; }
        EntityManager& GetEntityManager() { return *m_entityManager; }
        SubsystemManager& GetSubsystemManager() { return *m_subsystemManager; }

        void Run();

        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

    private:
        Application();
        ~Application() = default;

        bool m_applicationIsRunning = true;

        void HandleViewEvent(const sf::Event& event);

        // Order is important because of destructions
        std::unique_ptr<SubsystemManager> m_subsystemManager;
        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<EntityManager> m_entityManager;
    };
};


