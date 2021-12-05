#pragma once
#include <SFML/Graphics.hpp>

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
        sf::RenderWindow m_window;
    };
};


