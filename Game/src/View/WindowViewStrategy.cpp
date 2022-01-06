#include "WindowViewStrategy.h"

#include "../Debug/Logger.h"
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
            LOG_INFO("Created WindowViewStrategy");
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
            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
            {
                auto sftext = static_cast<sf::Text>(text);
                sftext.setFont(font);
                m_window.draw(sftext);
            }         
        }

        void WindowViewStrategy::PostRender()
        {
            m_window.display();
        }

        sf::Vector2i WindowViewStrategy::GetMousePosition()
        {
            return sf::Mouse::getPosition(m_window);
        }
    };
};