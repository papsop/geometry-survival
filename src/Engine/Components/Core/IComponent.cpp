#include "IComponent.h"

#include "../../Core/GameObject/GameObject.h"
#include "../../Application.h"

namespace Engine
{
    // view

    IRenderableShapeComponent::IRenderableShapeComponent(GameObject& obj, view::Renderable_Type renderableType, view::Layer layer)
        : IComponent(obj)
        , c_Layer(layer)
        , m_renderableTransform()
        , m_renderable(renderableType)
    {
        switch (renderableType)
        {
        case view::Renderable_Type::SHAPE:
            m_renderable.shape = { &m_renderableTransform };
            break;
        case view::Renderable_Type::CIRCLE:
            m_renderable.circle = { &m_renderableTransform };
            break;
        case view::Renderable_Type::RECTANGLE:
            m_renderable.rectangle = { &m_renderableTransform };
            break;
        };

        // activate based on Owner gameObject
        if (obj.IsActive()) Activate();
    };

    IRenderableTextComponent::IRenderableTextComponent(GameObject& obj)
        : IComponent(obj)
        , m_ownerTransform(obj.GetTransform())
    {};

	void IComponent::Activate()
	{
        if (!m_isActive)
        {
            VirtualOnActivated();
            m_isActive = true;
        }
	}

	void IComponent::Deactivate()
	{
		if (m_isActive)
		{
			VirtualOnDeactivated();
			m_isActive = false;
		}
	}

};