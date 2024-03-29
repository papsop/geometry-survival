#include "VisualDebugContext.h"
#include "../Managers/RenderManager.h"

namespace Engine
{

  VisualDebugContext::VisualDebugContext(RenderManager& renderManager)
    : m_renderManager(renderManager)
  {

  }

  void VisualDebugContext::DebugRenderLine(ITransform::PositionSpace space, math::Vec2 a, math::Vec2 b, sf::Color color)
  {
    if (!m_window)
      return;

		auto p1 = m_renderManager.coordsPosToPixelsPos(a);
		auto p2 = m_renderManager.coordsPosToPixelsPos(b);

		sf::Vertex line[] = {
							sf::Vertex(p1, color),
			sf::Vertex(p2, color)
		};
		m_window->draw(line, 2, sf::Lines);
  }

  void VisualDebugContext::DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color)
  {
    if (!m_window)
      return;

    auto sfmlPosition = m_renderManager.coordsPosToPixelsPos(center);
    auto sfmlRadius = m_renderManager.coordToPixel(radius);

    sf::CircleShape circle(sfmlRadius);
    circle.setOutlineColor(color);
    circle.setOutlineThickness(2.0f);
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setOrigin({ sfmlRadius, sfmlRadius });
    circle.setPosition(sfmlPosition);
    m_window->draw(circle);
  }

  void VisualDebugContext::DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor)
  {
    if (!m_window)
      return;

  }

  void VisualDebugContext::DebugRenderText(ITransform::PositionSpace space, std::string value, math::Vec2 position, bool shouldCenter, float size, sf::Color color)
  {
    if (!m_window)
      return;

    auto sfmlPosition = m_renderManager.coordsPosToPixelsPos(position);

    sf::Text text;
    text.setFont(m_renderManager.GetFont());
    text.setPosition(sfmlPosition);
    text.setFillColor(color);
    text.setString(value);
    text.setCharacterSize(size);
    m_window->draw(text);
  }

}