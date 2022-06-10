#include "WindowViewStrategy.h"

#include "../Debug/Logger.h"
#include "../Managers/ViewManager.h"
#include "../Application.h"
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Engine
{
    class Application;
    namespace view
    {
        WindowViewStrategy::WindowViewStrategy(TEventCallback handleEvent)
            : IViewStrategy(handleEvent)
        {
            auto width = ConfigManager::Get().GetValue<int>("window_width");
            auto height = ConfigManager::Get().GetValue<int>("window_height");
            auto name = ConfigManager::Get().GetValue<std::string>("window_name");
            auto fullscreen = ConfigManager::Get().GetValue<bool>("window_fullscreen");

            sf::VideoMode videoMode(width, height, 32);
            uint32 style = sf::Style::Default;
            if (fullscreen)
                style = sf::Style::Fullscreen;

            m_window = std::make_unique<sf::RenderWindow>(videoMode, name, style);

            if (!m_consoleFont.loadFromFile("assets/arial.ttf"))
            {
                LOG_ERROR("Unable to load console font");
            }
            LOG_DEBUG("Created WindowViewStrategy");
        }

        WindowViewStrategy::~WindowViewStrategy()
        {
            EventManager::Get().DispatchEvent(E_WindowClosed());
            m_window->close();
        }

        void WindowViewStrategy::PollEvents()
        {
            sf::Event event;
            while (m_window->pollEvent(event))
                m_handleEventLambda(event);
        }
        // ==============================================
        // Conversions
        // ==============================================
		sf::CircleShape WindowViewStrategy::CircleToSFMLCircleShape(const view::Circle& circle)
		{
            // convert box2d to sfml
            auto sfmlPosition = ViewManager::Get().coordsToPixels(circle.Transform->Position);
            auto sfmlRadius = ViewManager::Get().coordToPixel(circle.Radius);
            auto sfmlScale = sf::Vector2f(circle.Transform->Scale.x, circle.Transform->Scale.y);
            auto sfmlAngle = Box2DRotationToSFML(circle.Transform->Rotation);

            // create sfml circle shape
			auto obj = sf::CircleShape();
			obj.setPointCount(50);
			obj.setRadius(sfmlRadius);
			obj.setFillColor(circle.FillColor);
			obj.setPosition(sfmlPosition);
			// SFML uses bearings, north is 0 and east is 90 (the fuck?)
			obj.setRotation(sfmlAngle);
			obj.setScale(sfmlScale);
			obj.setOrigin(sf::Vector2f(circle.Radius, circle.Radius));
			return obj;
		}

		sf::CircleShape WindowViewStrategy::ShapeToSFMLCircleShape(const view::Shape& shape)
		{
			// convert box2d to sfml
			auto sfmlPosition = ViewManager::Get().coordsToPixels(shape.Transform->Position);
            auto sfmlRadius = ViewManager::Get().coordToPixel(shape.Radius);
			auto sfmlScale = sf::Vector2f(shape.Transform->Scale.x, shape.Transform->Scale.y);
            auto sfmlAngle = Box2DRotationToSFML(shape.Transform->Rotation);

			// create sfml circle shape
			auto obj = sf::CircleShape();
			obj.setPointCount(shape.PointCount);
			obj.setRadius(sfmlRadius);
			obj.setPosition(sfmlPosition);
            obj.setFillColor(shape.Color);
			// SFML uses bearings, north is 0 and east is 90 (the fuck?)
			obj.setRotation(sfmlAngle);
			obj.setScale(sfmlScale);
            obj.setOrigin({ sfmlRadius, sfmlRadius });
			return obj;
		}

		sf::RectangleShape WindowViewStrategy::RectangleToSFMLRectangleShape(const view::Rectangle& rectangle)
		{
            //convert box2d to sfml
			auto sfmlPosition = ViewManager::Get().coordsToPixels(rectangle.Transform->Position);
			auto sfmlSize = ViewManager::Get().coordsToPixels(rectangle.Size);
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
            //convert box2d to sfml
            sf::Vector2f sfmlPosition;
            if (text.UseScreenPosition)
            {
                sfmlPosition = m_window->mapPixelToCoords(BVec2ToVector2i(text.Transform->Position));
            }
            else
            {
                sfmlPosition = ViewManager::Get().coordsToPixels(text.Transform->Position);
            }

            auto obj = sf::Text();
            obj.setFont(m_consoleFont);
            obj.setCharacterSize(text.Size);
            obj.setFillColor(text.Color);
            obj.setString(text.Value);
			if (text.ShouldCenter)
			{
				// center text, need to do it after setting font
				sf::FloatRect textRect = obj.getLocalBounds();
				obj.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
			}
            obj.setPosition(sfmlPosition);
            
            return obj;
		}

		float WindowViewStrategy::Box2DRotationToSFML(float angle)
		{
			return 360.0f - math::RAD_TO_DEG(angle);
		}

		sf::Vector2i WindowViewStrategy::BVec2ToVector2i(b2Vec2 vec)
		{
            return { static_cast<int>(vec.x), static_cast<int>(vec.y) };
            //return { vec.x, vec.y };
		}

		void WindowViewStrategy::DrawWindowGrid()
		{
            float fGridSize = static_cast<float>(m_gridSize);
			for (int i = -m_gridSize; i < m_gridSize; i++)
			{
                float fi = static_cast<float>(i);
				DebugRenderLine({ fi, -fGridSize }, { fi, fGridSize }, sf::Color::White);
				DebugRenderLine({ -fGridSize, fi}, { fGridSize, fi }, sf::Color::White);
			}
		}

		// ==============================================

        void WindowViewStrategy::PreRender()
        {
            m_window->clear();
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
            m_window->draw(ShapeToSFMLCircleShape(shape));   
        }

        void WindowViewStrategy::Render(const Circle& circle)
        {
            m_window->draw(CircleToSFMLCircleShape(circle));
        }

		void WindowViewStrategy::Render(const Rectangle& rectangle)
		{
			m_window->draw(RectangleToSFMLRectangleShape(rectangle));
		}

        void WindowViewStrategy::Render(const Text& text)
        {
            m_window->draw(TextToSFMLText(text));
        }

        void WindowViewStrategy::Render(const Line& line)
        {
            m_window->draw(line.Points, 2, sf::Lines);
        }
        
        // ==================================================================================
        // Debug Renders

        void WindowViewStrategy::DebugRenderLine(Engine::math::Vec2 a, Engine::math::Vec2 b, sf::Color color)
		{
            auto p1 = ViewManager::Get().coordsToPixels(a);
            auto p2 = ViewManager::Get().coordsToPixels(b);

			sf::Vertex line[] = {
                sf::Vertex(p1, color),
				sf::Vertex(p2, color)
			};
			m_window->draw(line, 2, sf::Lines);
		}

		void WindowViewStrategy::DebugRenderCircle(Engine::math::Vec2 center, float radius, sf::Color color)
		{
			auto sfmlPosition = ViewManager::Get().coordsToPixels(center);
			auto sfmlRadius = ViewManager::Get().coordToPixel(radius);

            sf::CircleShape circle(sfmlRadius);
            circle.setOutlineColor(color);
            circle.setOutlineThickness(2.0f);
            circle.setFillColor(sf::Color(0, 0, 0, 0));
            circle.setOrigin({ sfmlRadius, sfmlRadius });
            circle.setPosition(sfmlPosition);
            m_window->draw(circle);
		}

		void WindowViewStrategy::DebugRenderRectangle(Engine::math::Vec2 center, Engine::math::Vec2 size, float angle, sf::Color color)
		{
			//convert box2d to sfml
			auto sfmlPosition = ViewManager::Get().coordsToPixels(center);
			auto sfmlSize = ViewManager::Get().coordsToPixels(size);
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
            m_window->draw(obj);
		}

		void WindowViewStrategy::DebugRenderText(std::string text, Engine::math::Vec2 position, float size, sf::Color color)
		{
			//convert box2d to sfml
			auto sfmlPosition = ViewManager::Get().coordsToPixels(position);

			sf::Font font;
			if (!font.loadFromFile("assets/arial.ttf"))
			{
				// error...
			}

			auto obj = sf::Text();
			obj.setFont(font);
			obj.setCharacterSize(size);
			obj.setFillColor(color);
			// center text, need to do it after setting font
			sf::FloatRect textRect = obj.getLocalBounds();
			obj.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
			obj.setPosition(sfmlPosition);

            m_window->draw(obj);
		}

		// ==================================================================================


        void WindowViewStrategy::PostRender()
        {
            if(ViewManager::Get().IsDebugDrawing())
                DrawWindowGrid();
            m_window->display();
        }

        void WindowViewStrategy::SetView(const CameraData& cameraData)
        {
            sf::View view;
            view.setCenter(ViewManager::Get().coordsToPixels(cameraData.Center));
            auto sfmlSize = ViewManager::Get().coordsToPixels(cameraData.Size);
            sfmlSize.y *= -1; // because coordsToPixels reverts y;
            view.setSize(sfmlSize);
            view.setViewport({ .0f, .0f, 1.f, 1.f });
            m_window->setView(view);
        }

        sf::Vector2f WindowViewStrategy::GetMousePosition()
        {
            auto pos = sf::Mouse::getPosition(*m_window);
            return m_window->mapPixelToCoords(pos);
        }

	};
};