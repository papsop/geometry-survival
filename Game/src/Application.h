#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Managers/AllManagers.h"
#include "View/ViewManager.h"

namespace Game
{

    //class InputManager;
    //class RenderManager;

    class Application
    {
    public:
        static Application& Instance()
        {
            static Application instance;
            return instance;
        }

        InputManager& GetInputManager() { return *m_inputManager; }
        RenderManager& GetRenderManager() { return *m_renderManager; }
        EntityManager& GetEntityManager() { return *m_entityManager; }
        SubsystemManager& GetSubsystemManager() { return *m_subsystemManager; }

        void Run();

        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

        sf::Vector2i GetMousePosition();
    private:
        Application();
        ~Application() = default;

        bool m_applicationIsRunning = true;

        void HandleWindowEvent(const sf::Event& event);

        // Order is important because of destructions
        std::unique_ptr<SubsystemManager> m_subsystemManager;
        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<RenderManager> m_renderManager;
        std::unique_ptr<view::ViewManager> m_viewManager;
        std::unique_ptr<EntityManager> m_entityManager;
    };
};


