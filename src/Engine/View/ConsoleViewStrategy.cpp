#include "ConsoleViewStrategy.h"

#include <iostream>

namespace Engine
{
    class Application;
    namespace view
    {
        ConsoleViewStrategy::ConsoleViewStrategy()
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

        void ConsoleViewStrategy::PostRender()
        {
            std::cout << "==============ConsoleViewStrategy::PostRender()==============" << std::endl;
        }
    };
};