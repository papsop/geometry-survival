#include "ConsoleViewStrategy.h"

#include <iostream>

namespace Game
{
    class Application;
    namespace view
    {
        ConsoleViewStrategy::ConsoleViewStrategy(std::function<void(const sf::Event& event)> handleEvent)
            : IViewStrategy(handleEvent)
        {
        }

        void ConsoleViewStrategy::PollEvents()
        {
            std::cout << "==============ConsoleViewStrategy::PollEvents()==============" << std::endl;
        }

        void ConsoleViewStrategy::PreRender()
        {
            std::cout << "==============ConsoleViewStrategy::PreRender()==============" << std::endl;
        }

        void ConsoleViewStrategy::Render(const Shape& shape)
        {
            std::cout << "Rendering shape" << std::endl;
        }

        void ConsoleViewStrategy::PostRender()
        {
            std::cout << "==============ConsoleViewStrategy::PostRender()==============" << std::endl;
        }
    };
};