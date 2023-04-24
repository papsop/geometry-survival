#include "VisualDebugContext.h"

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


  }

  void VisualDebugContext::DebugRenderCircle(ITransform::PositionSpace space, math::Vec2 center, float radius, sf::Color color)
  {
    if (!m_window)
      return;


  }

  void VisualDebugContext::DebugRenderRectangle(ITransform::PositionSpace space, math::Vec2 center, math::Vec2 size, float angle, sf::Color color, sf::Color fillColor)
  {
    if (!m_window)
      return;

  }

  void VisualDebugContext::DebugRenderText(ITransform::PositionSpace space, std::string text, math::Vec2 position, bool shouldCenter, float size, sf::Color color)
  {
    if (!m_window)
      return;


  }

}