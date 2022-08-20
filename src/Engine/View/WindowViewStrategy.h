#pragma once
#include "IViewStrategy.h"
#include "../Core/Events.h"
#include <SFML/Graphics.hpp>
#include "../Managers/ConfigManager.h"

namespace Engine
{
    namespace view
    {
        class WindowViewStrategy : public IViewStrategy, public IConfigurable
        {
        public:
            WindowViewStrategy(ViewManager& viewManager);
            ~WindowViewStrategy();

            void PollEvents() override;

            void PreRender() override;
            void RenderRenderable(Renderable& renderable) override;
            void PostRender() override;


// 			void DebugRenderLine(Engine::math::Vec2 a, Engine::math::Vec2 b, sf::Color color) override;
// 			void DebugRenderCircle(Engine::math::Vec2 center, float radius, sf::Color color) override;
//             void DebugRenderRectangle(Engine::math::Vec2 center, Engine::math::Vec2 size, float angle, sf::Color color, sf::Color fillColor) override;
//             void DebugRenderText(std::string text, Engine::math::Vec2 position, float size, sf::Color color) override;

            void SetView(const CameraData& cameraData) override;
            sf::Vector2f GetMousePosition() override;

            ConfigurableData GetConfigurableData() override;

        private:
            // conversions
//             sf::CircleShape     CircleToSFMLCircleShape(const view::Circle& circle);
// 			sf::CircleShape     ShapeToSFMLCircleShape(const view::Shape& shape);
//             sf::RectangleShape  RectangleToSFMLRectangleShape(const view::Rectangle& rectangle);
//             sf::Text            TextToSFMLText(const view::Text& text);
			float               Box2DRotationToSFML(float angle);
			sf::Vector2i        BVec2ToVector2i(b2Vec2 vec);
            sf::CircleShape         GetSFMLCircleFromShape(const ITransform::AbsoluteTransform& transform, const view::Renderable::Shape& shape);
            // ==============

            void RenderShape(const Renderable& renderable);

            void ReloadWindow();

            std::unique_ptr<sf::RenderWindow> m_window;

            sf::Font m_consoleFont;

			int m_windowWidth;
			int m_windowHeight;
            int m_windowFullscreen;
			std::string m_windowName;

        };
    };
};


