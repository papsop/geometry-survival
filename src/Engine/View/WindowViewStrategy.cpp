#include "WindowViewStrategy.h"

#include "../Debug/Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Engine
{
    class Application;
    namespace view
    {
        WindowViewStrategy::WindowViewStrategy(std::function<void(const sf::Event& event)> handleEvent)
            : IViewStrategy(handleEvent)
            , m_window(sf::VideoMode(1024, 768), "Dungeons & Geometry")
        {
            LOG_DEBUG("Created WindowViewStrategy");
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

        void WindowViewStrategy::Render(const Circle& circle)
        {
            m_window.draw(static_cast<sf::CircleShape>(circle));
        }

        void WindowViewStrategy::Render(const Text& text)
        {
            auto sftext = static_cast<sf::Text>(text);
            sf::Font font;
            if (!font.loadFromFile("assets/arial.ttf"))
            {
                // error...
            }
            sftext.setFont(font);

            if (text.ShouldCenter)
            {
                // center text, need to do it after setting font
                sf::FloatRect textRect = sftext.getLocalBounds();
                sftext.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
            }

            m_window.draw(sftext);
        }

        void WindowViewStrategy::Render(const Line& line)
        {
            m_window.draw(line.Points, 2, sf::Lines);
        }
        
        // ==================================================================================
        // Debug Renders

        void WindowViewStrategy::DebugRenderLine(sf::Vector2f a, sf::Vector2f b, sf::Color color)
		{
            sf::Vertex line[] = {
                sf::Vertex(a, color),
                sf::Vertex(b, color)
            };
            m_window.draw(line, 2, sf::Lines);
		}

		void WindowViewStrategy::DebugRenderCircle(sf::Vector2f center, float radius, sf::Color color)
		{
            sf::CircleShape circle(radius);
            circle.setOutlineColor(color);
            circle.setOutlineThickness(2.0f);
            circle.setFillColor(sf::Color(0, 0, 0, 0));
            circle.setOrigin({radius, radius});
            circle.setPosition(center);
            m_window.draw(circle);
		}

        // ==================================================================================


        void WindowViewStrategy::PostRender()
        {
            m_window.display();
        }

        void WindowViewStrategy::SetView(const sf::View& view)
        {
            m_window.setView(view);
        }

        sf::Vector2i WindowViewStrategy::GetMousePosition()
        {
            return sf::Mouse::getPosition(m_window);
        }

	};
};