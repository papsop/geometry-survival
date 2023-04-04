#pragma once
#include "IViewStrategy.h"
#include "../Core/Events.h"
#include <SFML/Graphics.hpp>
#include "../Managers/ConfigManager.h"

namespace Engine{
namespace view{
  class WindowViewStrategy : public IViewStrategy, public IConfigurable
    {
    public:
      WindowViewStrategy(ViewManager& viewManager);
      ~WindowViewStrategy();

      void PollEvents() override;

      void PreRender() override;
      void RenderRenderable(Renderable& renderable) override;
      void PostRender() override;

      void DebugRenderLine(ITransform::PositionSpace space, math::Vec2 a, math::Vec2 b, sf::Color color) override;
      void DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color) override;
      void DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor) override;
      void DebugRenderText(ITransform::PositionSpace space, std::string text, math::Vec2 position, bool shouldCenter, float size, sf::Color color) override;

      void SetView(CameraData cameraData) override;
      sf::Vector2f GetMousePosition() override;

      math::Vec2 GetResolution() override;

      void GetConfigurableData(ConfigurableData& data) override;

      sf::Vector2i MapCoordsToPixel(sf::Vector2f coords) override;
      sf::Vector2f MapPixelToCoords(sf::Vector2i pixel) override;

      void SetResolution(Engine::math::Vec2 resolution) override;
      void SetFullscreen(bool fullscreen) override;
      void ReloadView() override;

      void Update(float dt) override;

    private:
      float                   Box2DRotationToSFML(float angle);
      sf::Vector2i            BVec2ToVector2i(b2Vec2 vec);
      sf::Vector2f            CameraSpaceToCoords(math::Vec2 vec);

      sf::CircleShape         GetSFMLCircleFromShape(const ITransform::AbsoluteTransform& transform, const view::Renderable::Shape& shape);
      sf::RectangleShape      GetSFMLRectangleFromRectangle(const ITransform::AbsoluteTransform& transform, const view::Renderable::Rectangle& rect);
      sf::Text                GetSFMLTextFromText(const ITransform::AbsoluteTransform& transform, const view::Renderable::Text& text);
      // ==============

      void RenderShape(const Renderable& renderable);

      std::unique_ptr<sf::RenderWindow> m_window;

      sf::Clock m_deltaClock;
      sf::Font m_consoleFont;

      int m_windowWidth;
      int m_windowHeight;
      int m_windowFullscreen;
      std::string m_windowName;
  };

};
};


