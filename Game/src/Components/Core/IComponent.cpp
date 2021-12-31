#include "IComponent.h"

#include "../../Core/GameObject.h"

namespace Game
{
    IRenderableShapeComponent::IRenderableShapeComponent(GameObject& obj, int zIndex)
        : IComponent(obj)
        , ZIndex(zIndex)
        , m_ownerTransform(obj.GetTransform())
    {};

    IRenderableTextComponent::IRenderableTextComponent(GameObject& obj)
        : IComponent(obj)
        , m_ownerTransform(obj.GetTransform())
    {};
};