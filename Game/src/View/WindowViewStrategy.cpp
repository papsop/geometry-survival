#include "WindowViewStrategy.h"

#include <iostream>
namespace Game
{
    class Application;
    namespace view
    {
        WindowViewStrategy::WindowViewStrategy(std::function<void(const sf::Event& event)> handleEvent)
            : IViewStrategy(handleEvent)
            , m_window(sf::VideoMode(1024, 768), "Dungeons & Geometry")
        {
            m_font.loadFromFile("arial.ttf");
        }

        WindowViewStrategy::~WindowViewStrategy()
        {
            m_window.close();
        }

        void WindowViewStrategy::PollEvents()
        {
            sf::Event event;
            while (m_window.pollEvent(event))
                m_handleEventLambda(event);
        }

        void WindowViewStrategy::PreRender()
        {
            m_window.clear();
        }

        void WindowViewStrategy::Render(const Shape &shape)
        {
            m_window.draw(static_cast<sf::CircleShape>(shape));   
        }

        void WindowViewStrategy::Render(const Text& text)
        {
            m_window.draw(static_cast<sf::Text>(text));
        }

        void WindowViewStrategy::PostRender()
        {
            m_window.display();
        }
    };
};