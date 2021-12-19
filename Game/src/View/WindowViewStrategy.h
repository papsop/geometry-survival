#pragma once
#include "IViewStrategy.h"

#include <SFML/Graphics.hpp>

namespace Game
{
    namespace view
    {
        class WindowViewStrategy : public IViewStrategy
        {
        public:
            WindowViewStrategy(std::function<void(const sf::Event& event)> handleEvent);
            ~WindowViewStrategy();

            void PollEvents() override;

            void PreRender() override;
            void Render(const Shape& shape) override;
            void PostRender() override;
        private:
            sf::RenderWindow m_window;
        };
    };
};


