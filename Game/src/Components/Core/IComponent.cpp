#include "IComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

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

    IDebugDrawComponent::IDebugDrawComponent()
    {
        VIEWSUBSYSTEM_REGISTER(this);
    }
    IDebugDrawComponent::~IDebugDrawComponent()
    {
        VIEWSUBSYSTEM_UNREGISTER(this);
    }
};