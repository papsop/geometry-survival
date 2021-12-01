#pragma once
#include <SFML/Graphics.hpp>

namespace Game
{
    class Application
    {
    public:
        Application() : m_window(sf::VideoMode(200, 200), "SFML works!") {}
        void Run();

        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

    private:
        sf::RenderWindow m_window;
    };
};


