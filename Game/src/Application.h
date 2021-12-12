#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Singletons/InputManager.h"
#include "Singletons/RenderManager.h"
#include "Singletons/EntityManager.h"

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

        void Run();

        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

        sf::Vector2i GetMousePosition();
    private:
        Application();
        ~Application() = default;

        sf::RenderWindow m_window;

        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<RenderManager> m_renderManager;
        std::unique_ptr<EntityManager> m_entityManager;
    };
};


