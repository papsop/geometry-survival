#include "WindowViewStrategy.h"

namespace Game
{
    class Application;
    namespace view
    {
        WindowViewStrategy::WindowViewStrategy(std::function<void(const sf::Event& event)> handleEvent)
            : IViewStrategy(handleEvent)
            , m_window(sf::VideoMode(1024, 768), "Dungeons & Geometry")
        {
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

        void WindowViewStrategy::PostRender()
        {
            m_window.display();
        }
    };
};