#include "BoxCollider.h"

#include "../../Core/GameObject.h"

namespace Game
{
    BoxCollider::BoxCollider(GameObject& obj)
        : IRenderableShapeComponent(obj, 20)
        , m_shape(obj.GetTransform())
    {

    }

    const view::Shape& BoxCollider::GetRenderableShape()
    {
        return m_shape;
    }
};