#pragma once
#include "IViewStrategy.h"

#include <SFML/Graphics.hpp>

namespace Engine
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
            void Render(const Circle& circle) override;
            void Render(const Text& text) override;
            void Render(const Line& line) override;
            void PostRender() override;

            sf::Vector2i GetMousePosition() override;

            void DebugRenderLine(sf::Vector2f a, sf::Vector2f b, sf::Color color) override;
            void DebugRenderCircle(sf::Vector2f center, float radius, sf::Color color) override;

        private:
            sf::RenderWindow m_window;
            sf::Font m_font;
        };
    };
};


