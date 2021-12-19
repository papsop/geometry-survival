#include "TriangleComponent.h"

#include "../GameObject.h"

namespace Game
{
    TriangleComponent::TriangleComponent(GameObject& obj, sf::Color color)
        : IComponent(obj)
        , IRenderableShape()
        , m_ownerTransform(m_owner.GetTransform())
    {
        m_shape.PointCount = 3;
        m_shape.Color = color;
        m_shape.Radius = 50;
    }

    const view::Shape& TriangleComponent::GetRenderableShape()
    {
        m_shape.ImportTransform(m_ownerTransform);
        return m_shape;
    }
};