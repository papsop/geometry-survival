#include "WindowViewStrategy.h"

#include "../Debug/Logger.h"
#include "../Managers/SubsystemManager.h"
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
        // ==============================================
        // Conversions
        // ==============================================
		sf::CircleShape WindowViewStrategy::CircleToSFMLCircleShape(const view::Circle& circle)
		{
            // convert box2d to sfml
            auto sfmlPosition = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(circle.Transform->Position);
            auto sfmlRadius = SubsystemManager::Get().GetViewSubsystem().coordToPixel(circle.Radius);
            auto sfmlScale = sf::Vector2f(circle.Transform->Scale.x, circle.Transform->Scale.y);

            // create sfml circle shape
			auto obj = sf::CircleShape();
			obj.setPointCount(50);
			obj.setRadius(sfmlRadius);
			obj.setFillColor(circle.FillColor);
			obj.setPosition(sfmlPosition);
			// SFML uses bearings, north is 0 and east is 90 (the fuck?)
			float angle = 360.0f - (circle.Transform->Rotation - 90.0f);
			obj.setRotation(angle);
			obj.setScale(sfmlScale);
			obj.setOrigin(sf::Vector2f(circle.Radius, circle.Radius));
			return obj;
		}

		sf::CircleShape WindowViewStrategy::ShapeToSFMLCircleShape(const view::Shape& shape)
		{
			// convert box2d to sfml
			auto sfmlPosition = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(shape.Transform->Position);
            auto sfmlRadius = SubsystemManager::Get().GetViewSubsystem().coordToPixel(shape.Radius);
			auto sfmlScale = sf::Vector2f(shape.Transform->Scale.x, shape.Transform->Scale.y);

			// create sfml circle shape
			auto obj = sf::CircleShape();
			obj.setPointCount(shape.PointCount);
			obj.setRadius(sfmlRadius);
			obj.setPosition(sfmlPosition);
			// SFML uses bearings, north is 0 and east is 90 (the fuck?)
			float angle = 360.0f - (shape.Transform->Rotation - 90.0f);
			obj.setRotation(angle);
			obj.setScale(sfmlScale);
            obj.setOrigin({ sfmlRadius, sfmlRadius });
			return obj;
		}

		sf::RectangleShape WindowViewStrategy::RectangleToSFMLRectangleShape(const view::Rectangle& rectangle)
		{
            //convert box2d to sfml
			auto sfmlPosition = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(rectangle.Transform->Position);
			auto sfmlSize = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(rectangle.Size);
            sfmlSize.y  = 2 * std::fabsf(sfmlSize.y);
            sfmlSize.x  = 2 * sfmlSize.x;
			auto sfmlScale = sf::Vector2f(rectangle.Transform->Scale.x, rectangle.Transform->Scale.y);
            auto sfmlAngle = Box2DRotationToSFML(rectangle.Transform->Rotation);

            // create SFML rectangle
            auto obj = sf::RectangleShape();
            obj.setFillColor(rectangle.FillColor);
            obj.setSize(sfmlSize);
			obj.setRotation(sfmlAngle);
            obj.setScale(sfmlScale);
            obj.setOrigin(sfmlSize.x / 2, sfmlSize.y / 2);
            obj.setPosition(sfmlPosition);
            return obj;
		}

		sf::Text WindowViewStrategy::TextToSFMLText(const view::Text& text)
		{
            return {};
		}

		float WindowViewStrategy::Box2DRotationToSFML(float angle)
		{
			return 360.0f - math::RAD_TO_DEG(angle);
		}

		// ==============================================

        void WindowViewStrategy::PreRender()
        {
            m_window.clear();
        }

		void WindowViewStrategy::RenderRenderable(const Renderable& renderable)
		{
            switch (renderable.type)
            {
            case view::RENDERABLE_TYPE::SHAPE: 
                Render(renderable.shape); 
                break;
            case view::RENDERABLE_TYPE::CIRCLE:
				Render(renderable.circle);
				break;
            case view::RENDERABLE_TYPE::RECTANGLE:
				Render(renderable.rectangle);
				break;
            }
		}

        void WindowViewStrategy::Render(const Shape &shape)
        {
            m_window.draw(ShapeToSFMLCircleShape(shape));   
        }

        void WindowViewStrategy::Render(const Circle& circle)
        {
            m_window.draw(CircleToSFMLCircleShape(circle));
        }

		void WindowViewStrategy::Render(const Rectangle& rectangle)
		{
			m_window.draw(RectangleToSFMLRectangleShape(rectangle));
		}

        void WindowViewStrategy::Render(const Text& text)
        {
            auto sftext = TextToSFMLText(text);
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

        void WindowViewStrategy::DebugRenderLine(Engine::math::Vec2 a, Engine::math::Vec2 b, sf::Color color)
		{
            //sf::Vertex line[] = {
            //    sf::Vertex(a, color),
            //    sf::Vertex(b, color)
            //};
            //m_window.draw(line, 2, sf::Lines);
		}

		void WindowViewStrategy::DebugRenderCircle(Engine::math::Vec2 center, float radius, sf::Color color)
		{
			auto sfmlPosition = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(center);
			auto sfmlRadius = SubsystemManager::Get().GetViewSubsystem().coordToPixel(radius);

            sf::CircleShape circle(sfmlRadius);
            circle.setOutlineColor(color);
            circle.setOutlineThickness(2.0f);
            circle.setFillColor(sf::Color(0, 0, 0, 0));
            circle.setOrigin({ sfmlRadius, sfmlRadius });
            circle.setPosition(sfmlPosition);
            m_window.draw(circle);
		}

		void WindowViewStrategy::DebugRenderRectangle(Engine::math::Vec2 center, Engine::math::Vec2 size, float angle, sf::Color color)
		{
			//convert box2d to sfml
			auto sfmlPosition = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(center);
			auto sfmlSize = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(size);
			sfmlSize.y = 2 * std::fabsf(sfmlSize.y);
			sfmlSize.x = 2 * sfmlSize.x;
			auto sfmlAngle = Box2DRotationToSFML(angle);

			// create SFML rectangle
			auto obj = sf::RectangleShape();
			obj.setOutlineColor(color);
            obj.setOutlineThickness(3);
			obj.setSize(sfmlSize);
			obj.setRotation(sfmlAngle);
			obj.setScale({1.0f, 1.0f});
			obj.setOrigin(sfmlSize.x / 2, sfmlSize.y / 2);
			obj.setPosition(sfmlPosition);
            m_window.draw(obj);
		}

        // ==================================================================================


        void WindowViewStrategy::PostRender()
        {
            m_window.display();
        }

        void WindowViewStrategy::SetView(const CameraData& cameraData)
        {
            sf::View view;
            view.setCenter(SubsystemManager::Get().GetViewSubsystem().coordsToPixels(cameraData.Center));
            auto sfmlSize = SubsystemManager::Get().GetViewSubsystem().coordsToPixels(cameraData.Size);
            sfmlSize.y *= -1; // because coordsToPixels reverts y;
            view.setSize(sfmlSize);
            view.setViewport({ .0f, .0f, 1.f, 1.f });
            m_window.setView(view);
        }

        sf::Vector2f WindowViewStrategy::GetMousePosition()
        {
            auto pos = sf::Mouse::getPosition(m_window);
            return m_window.mapPixelToCoords(pos);
        }

	};
};