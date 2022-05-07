#pragma once
#include "../View/Renderables.h"
#include "../Core/CameraData.h"
#include <SFML/window.hpp>
#include <functional>

namespace Engine
{
    class Application;
    namespace view
    {
        class IViewStrategy
        {
        public:
            using TEventCallback = std::function<void(const sf::Event& event)>;

            IViewStrategy(TEventCallback handleEvent)
            {
                m_handleEventLambda = handleEvent;
            }

            virtual ~IViewStrategy() = default;

            virtual void PollEvents() = 0;
            virtual void PreRender() = 0;
            virtual void RenderRenderable(const Renderable& renderable) = 0;
            virtual void Render(const Shape& shape) = 0;
            virtual void Render(const Circle& circle) = 0;
            virtual void Render(const Text& text) = 0;
            virtual void Render(const Rectangle& rectangle) = 0;
            virtual void Render(const Line& line) = 0;
            virtual void PostRender() = 0;

            virtual void DebugRenderLine(Engine::math::Vec2 a, Engine::math::Vec2 b, sf::Color color) = 0;
            virtual void DebugRenderCircle(Engine::math::Vec2 center, float radius, sf::Color color) = 0;
            virtual void DebugRenderRectangle(Engine::math::Vec2 center, Engine::math::Vec2 size, float angle, sf::Color color) = 0;
            virtual void DebugRenderText(std::string text, Engine::math::Vec2 position, float size, sf::Color color) = 0;

            virtual void SetView(const CameraData& cameraData) = 0;
            virtual sf::Vector2f GetMousePosition() = 0;
        protected:
            TEventCallback m_handleEventLambda;
        };
    }
}