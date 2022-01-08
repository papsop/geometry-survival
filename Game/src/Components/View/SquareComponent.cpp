#include "SquareComponent.h"
#include "../../Application.h"
#include "../../Core/GameObject.h"

namespace Game
{
    SquareComponent::SquareComponent(GameObject& obj, sf::Color color, int zIndex)
        : IRenderableShapeComponent(obj, zIndex)
        , m_shape(obj.GetTransform())
    {
        m_shape.PointCount = 3;
        m_shape.Color = color;
        m_shape.Radius = 50;

        VIEWSUBSYSTEM_REGISTER(this);
    }

    SquareComponent::~SquareComponent()
    {
        VIEWSUBSYSTEM_UNREGISTER(this);
    }

    const view::Shape& SquareComponent::GetRenderableShape()
    {
        return m_shape;
    }
};