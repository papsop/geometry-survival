#include "SquareComponent.h"

#include "../../Core/GameObject.h"

namespace Game
{
    SquareComponent::SquareComponent(GameObject& obj, sf::Color color)
        : IComponent(obj)
        , IRenderableShape()
        , m_ownerTransform(obj.GetTransform())
    {
        m_shape.PointCount = 4;
        m_shape.Color = color;
        m_shape.Radius = 50;
    }

    const view::Shape& SquareComponent::GetRenderableShape()
    {
        m_shape.ImportTransform(m_ownerTransform);
        return m_shape;
    }
};