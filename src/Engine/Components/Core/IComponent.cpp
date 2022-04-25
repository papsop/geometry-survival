#include "IComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

namespace Engine
{
    // view

    IRenderableShapeComponent::IRenderableShapeComponent(GameObject& obj, view::RENDERABLE_TYPE renderableType,int zIndex)
        : IComponent(obj)
        , ZIndex(zIndex)
        , m_renderableTransform()
        , m_renderable(renderableType)
    {
        switch (renderableType)
        {
        case view::RENDERABLE_TYPE::SHAPE:
            m_renderable.shape = { &m_renderableTransform };
            break;
        case view::RENDERABLE_TYPE::CIRCLE:
            m_renderable.circle = { &m_renderableTransform };
            break;
        case view::RENDERABLE_TYPE::RECTANGLE:
            m_renderable.rectangle = { &m_renderableTransform };
            break;
        };
    };

    IRenderableTextComponent::IRenderableTextComponent(GameObject& obj)
        : IComponent(obj)
        , m_ownerTransform(obj.GetTransform())
    {};
};