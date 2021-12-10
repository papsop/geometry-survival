#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace Game
{
    class Application
    {
    public:
        Application();
        void Run();

        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

        sf::Vector2i GetMousePosition();
    private:
        std::unique_ptr<sf::RenderWindow> m_window;
    };
};


