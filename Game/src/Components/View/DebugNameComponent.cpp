#include "DebugNameComponent.h"

#include "../../Core/GameObject.h"

namespace Game
{
    DebugNameComponent::DebugNameComponent(GameObject& obj)
        : IComponent(obj)
        , IRenderableText()
        , m_ownerTransform(obj.GetTransform())
    {
        m_renderableText.Value = m_owner.DebugName;
    }

    const view::Text& DebugNameComponent::GetRenderableText()
    {
        m_renderableText.ImportTransform(m_ownerTransform);
        return m_renderableText;
    }
};