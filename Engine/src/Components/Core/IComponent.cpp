#include "IComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

namespace Engine
{
    uint32_t IComponent::m_nextComponentID = 0;

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
        Application::Instance().GetSubsystemManager().GetViewSubsystem().RegisterComponent(this);
    }
    IDebugDrawComponent::~IDebugDrawComponent()
    {
    }
};