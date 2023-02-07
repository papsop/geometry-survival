#include "WindowViewStrategy.h"

#include "../Debug/Logger.h"
#include "../Managers/ViewManager.h"
#include "../Managers/UIManager.h"
#include "../Application.h"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Engine{
    class Application;
namespace view{
    WindowViewStrategy::WindowViewStrategy(ViewManager& viewManager)
        : IViewStrategy(viewManager)
    {
      // todo config
      ConfigManager::Get().RegisterCvar("window_width", &m_windowWidth, 1280);
      ConfigManager::Get().RegisterCvar("window_height", &m_windowHeight, 720);
      ConfigManager::Get().RegisterCvar("window_name", &m_windowName, std::string("Geometry survival"));
      ConfigManager::Get().RegisterCvar("window_fullscreen", &m_windowFullscreen, 0);

      ReloadView();

      if (!m_consoleFont.loadFromFile("assets/arial.ttf"))
      {
          LOG_ERROR("Unable to load console font");
      }
      LOG_DEBUG("Created WindowViewStrategy");
    }

    WindowViewStrategy::~WindowViewStrategy()
    {
      EventManager::Get().DispatchEvent(event::E_WindowClosed());
      m_window->close();
    }

    void WindowViewStrategy::PollEvents()
    {
      sf::Event event;
      while (m_window->pollEvent(event))
      {
        Engine::EventManager::Get().DispatchEvent(event::E_SFMLEvent(event));
      }
    }

		void WindowViewStrategy::ReloadView()
		{
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;
			sf::VideoMode videoMode(m_windowWidth, m_windowHeight, 32);
			uint32 style = sf::Style::Titlebar | sf::Style::Close;
			if (m_windowFullscreen)
				style = sf::Style::Fullscreen;

			m_window = std::make_unique<sf::RenderWindow>(videoMode, m_windowName, style, settings);
      m_window->setJoystickThreshold(10);
      UIManager::Get().SetSFMLWindow(*m_window);
		}

    // ==============================================
    // Conversions
    // ==============================================

 		float WindowViewStrategy::Box2DRotationToSFML(float angle)
 		{
 			return 360.0f - math::RAD_TO_DEG(angle);
 		}
 
 		sf::Vector2i WindowViewStrategy::BVec2ToVector2i(b2Vec2 vec)
 		{
      return { static_cast<int>(vec.x), static_cast<int>(vec.y) };
      //return { vec.x, vec.y };
 		}

		sf::Vector2f WindowViewStrategy::CameraSpaceToCoords(math::Vec2 vec)
		{
      sf::Vector2i ivec = BVec2ToVector2i(vec);
      return m_window->mapPixelToCoords(ivec);
		}

		// ==============================================

    void WindowViewStrategy::PreRender()
    {
      m_window->clear();
    }
        
		void WindowViewStrategy::RenderRenderable(Renderable& renderable)
		{
      switch (renderable.Type)
      {
      case Renderable::RenderableType::SHAPE:
        m_window->draw(GetSFMLCircleFromShape(renderable.Transform, renderable.shape));
        break;
      case Renderable::RenderableType::RECTANGLE:
        m_window->draw(GetSFMLRectangleFromRectangle(renderable.Transform, renderable.rectangle));
        break;
      case Renderable::RenderableType::TEXT:
        m_window->draw(GetSFMLTextFromText(renderable.Transform, renderable.text));
        break;
      }
		}

		sf::CircleShape WindowViewStrategy::GetSFMLCircleFromShape(const ITransform::AbsoluteTransform& transform, const view::Renderable::Shape& shape)
		{
      sf::Vector2f position;
      float angle;
      float radius;
      // convert Coords to pixel
      if (transform.Space == ITransform::PositionSpace::CameraSpace)
      {
        position    = CameraSpaceToCoords(transform.Position);
        radius      = shape.Radius;
      }
      else
      {
				position    = m_viewManager.coordsToPixels(transform.Position);
				radius      = m_viewManager.coordToPixel(shape.Radius);
      }
            
      angle = Box2DRotationToSFML(transform.Rotation); // shared in both

      // create sfml object
      auto obj = sf::CircleShape();
      obj.setPointCount(shape.PointCount);
      obj.setRadius(radius);
      obj.setPosition(position);
      obj.setFillColor(shape.Color);
      obj.setRotation(angle);
      obj.setScale({ 1,1 });
      obj.setOrigin({ radius, radius });
      return obj;
		}

    sf::RectangleShape WindowViewStrategy::GetSFMLRectangleFromRectangle(const ITransform::AbsoluteTransform& transform, const view::Renderable::Rectangle& rect)
    {
      //convert box2d to sfml
      sf::Vector2f sfmlPosition;
      sf::Vector2f sfmlSize;
      auto sfmlAngle = Box2DRotationToSFML(transform.Rotation);

      if (transform.Space == ITransform::PositionSpace::CameraSpace)
      {
        sfmlPosition  = CameraSpaceToCoords(transform.Position);
        sfmlSize      = { rect.Size.x, rect.Size.y };
      }
      else
      {
        sfmlPosition  = ViewManager::Get().coordsToPixels(transform.Position);
        sfmlSize      = ViewManager::Get().coordsToPixels(rect.Size);
      }

      // create SFML rectangle
      auto obj = sf::RectangleShape();
      obj.setOutlineColor(sf::Color::Transparent);
      obj.setOutlineThickness(3);
      obj.setSize(sfmlSize);
      obj.setFillColor(rect.FillColor);
      obj.setRotation(sfmlAngle);
      obj.setScale({ 1.0f, 1.0f });
      obj.setOrigin({0.0f, 0.0f});
      obj.setPosition(sfmlPosition);
      return obj;
    }

    sf::Text WindowViewStrategy::GetSFMLTextFromText(const ITransform::AbsoluteTransform& transform, const view::Renderable::Text& text)
    {
      //convert box2d to sfml
      auto sfmlPosition = ViewManager::Get().coordsToPixels(transform.Position);
      if (transform.Space == ITransform::PositionSpace::CameraSpace)
      {
        sfmlPosition = CameraSpaceToCoords(transform.Position);
      }
      else
      {
        sfmlPosition = ViewManager::Get().coordsToPixels(transform.Position);
      }

      auto obj = sf::Text();
      obj.setFont(m_consoleFont);
      obj.setString(std::string(text.Value));
      obj.setCharacterSize(text.Size);
      obj.setFillColor(text.Color);
      // center text, need to do it after setting font
      sf::FloatRect textRect = obj.getLocalBounds();
      if(text.ShouldCenter)
        obj.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
      obj.setPosition(sfmlPosition);

      return obj;
    }

    // ==================================================================================
    // Render each renderable type
    // ==================================================================================

		void WindowViewStrategy::RenderShape(const Renderable& renderable)
		{
// 			// convert box2d to sfml
// 			auto sfmlPosition = ViewManager::Get().coordsToPixels(shape.Transform->Position);
// 			auto sfmlRadius = ViewManager::Get().coordToPixel(shape.Radius);
// 			auto sfmlScale = sf::Vector2f(shape.Transform->Scale.x, shape.Transform->Scale.y);
// 			auto sfmlAngle = Box2DRotationToSFML(shape.Transform->Rotation);
// 
// 			// create sfml circle shape
// 			auto obj = sf::CircleShape();
// 			obj.setPointCount(shape.PointCount);
// 			obj.setRadius(sfmlRadius);
// 			obj.setPosition(sfmlPosition);
// 			obj.setFillColor(shape.Color);
// 			// SFML uses bearings, north is 0 and east is 90 (the fuck?)
// 			obj.setRotation(sfmlAngle);
// 			obj.setScale(sfmlScale);
// 			obj.setOrigin({ sfmlRadius, sfmlRadius });
// 			return obj;
		}

		// ==================================================================================
    // 
    // ==================================================================================

		void WindowViewStrategy::PostRender()
		{
			m_window->display();
		}

		// ==================================================================================
    // Debug Renders
    // ==================================================================================

    void WindowViewStrategy::DebugRenderLine(ITransform::PositionSpace space, math::Vec2 a, math::Vec2 b, sf::Color color)
 		{
      auto p1 = ViewManager::Get().coordsToPixels(a);
      auto p2 = ViewManager::Get().coordsToPixels(b);
 
 			sf::Vertex line[] = {
                sf::Vertex(p1, color),
 				sf::Vertex(p2, color)
 			};
 			m_window->draw(line, 2, sf::Lines);
 		}
 
 		void WindowViewStrategy::DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color)
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
 
 		void WindowViewStrategy::DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor)
 		{
 			//convert box2d to sfml
      sf::Vector2f sfmlPosition;
      sf::Vector2f sfmlSize;
 		  auto sfmlAngle = Box2DRotationToSFML(angle);

      if (space == ITransform::PositionSpace::CameraSpace)
      {
        sfmlPosition = CameraSpaceToCoords(center);
        sfmlSize = { size.x, size.y };
      }
      else
      {
        sfmlPosition = ViewManager::Get().coordsToPixels(center);
        sfmlSize = ViewManager::Get().coordsToPixels(size);
        sfmlSize.y = 2 * std::fabsf(sfmlSize.y);
        sfmlSize.x = 2 * sfmlSize.x;
      }
 
 			// create SFML rectangle
 			auto obj = sf::RectangleShape();
 			obj.setOutlineColor(color);
      obj.setOutlineThickness(3);
 			obj.setSize(sfmlSize);
      obj.setFillColor(fillColor);
 			obj.setRotation(sfmlAngle);
 			obj.setScale({1.0f, 1.0f});
 			obj.setOrigin(sfmlSize.x / 2, sfmlSize.y / 2);
 			obj.setPosition(sfmlPosition);
      m_window->draw(obj);
 		}
 
 		void WindowViewStrategy::DebugRenderText(ITransform::PositionSpace space, std::string text, math::Vec2 position, bool shouldCenter, float size, sf::Color color)
 		{
      ITransform::AbsoluteTransform absoluteTransform;
      view::Renderable::Text textObj;

      absoluteTransform.Position = position;
      absoluteTransform.Rotation = 0.0f;
      absoluteTransform.Scale = { 1.0f, 1.0f };
      absoluteTransform.Space = space;

      textObj.Color = color;
      textObj.ShouldCenter = shouldCenter;
      textObj.Size = size;
      // normally we would have an issue with storing c_str(), but since we are instantly rendering it -> it's fine
      textObj.Value = text.c_str();
      
      auto obj = GetSFMLTextFromText(absoluteTransform, textObj);

      m_window->draw(obj);
 		}

		// ==================================================================================

    void WindowViewStrategy::SetView(const CameraData& cameraData)
    {
      sf::View view;
      view.setCenter(ViewManager::Get().coordsToPixels(cameraData.Center));
      view.setSize(m_windowWidth, m_windowHeight);
      view.setViewport({ .0f, .0f, 1.f, 1.f });
      m_window->setView(view);
    }

    sf::Vector2f WindowViewStrategy::GetMousePosition()
    {
      auto pos = sf::Mouse::getPosition(*m_window);
      return m_window->mapPixelToCoords(pos);
    }

    math::Vec2 WindowViewStrategy::GetResolution()
    {
      return { static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight) };
    }

		void WindowViewStrategy::SetResolution(Engine::math::Vec2 resolution)
		{
      m_windowWidth   = resolution.x;
      m_windowHeight  = resolution.y;
		}

		void WindowViewStrategy::SetFullscreen(bool fullscreen)
		{
      m_windowFullscreen = fullscreen;
		}

    void WindowViewStrategy::GetConfigurableData(ConfigurableData& data)
    {
      data.push_back({ "window_width",          std::to_string(m_windowWidth) });
      data.push_back({ "window_height",         std::to_string(m_windowHeight) });
      data.push_back({ "window_fullscreen",     std::to_string(m_windowFullscreen) });
      data.push_back({ "window_name",                          m_windowName });
    }

    sf::Vector2i WindowViewStrategy::MapCoordsToPixel(sf::Vector2f coords)
    {
      return m_window->mapCoordsToPixel(coords);
    }

    sf::Vector2f WindowViewStrategy::MapPixelToCoords(sf::Vector2i pixel)
    {
      return m_window->mapPixelToCoords(pixel);
    }


}}