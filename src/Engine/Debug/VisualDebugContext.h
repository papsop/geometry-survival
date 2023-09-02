#pragma once
#include <SFML/Graphics.hpp>

#include "../Components/Core/ITransform.h"

namespace Engine {
class RenderManager;

class VisualDebugContext {
  friend class RenderManager;

 public:
  VisualDebugContext(RenderManager& renderManager);

  void DebugRenderLine(ITransform::PositionSpace space, math::Vec2 a, math::Vec2 b, sf::Color color);
  void DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color);
  void DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor);
  void DebugRenderText(ITransform::PositionSpace space, std::string text, math::Vec2 position, bool shouldCenter, float size, sf::Color color);

 private:
  RenderManager& m_renderManager;
  sf::RenderWindow* m_window;

  void SetRenderWindow(sf::RenderWindow* window) { m_window = window; };  // RenderManager sets this upon reloading view
};
}  // namespace Engine
