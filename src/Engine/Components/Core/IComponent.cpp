#include "IComponent.h"

#include "../../Core/GameObject/GameObject.h"
#include "../../Application.h"

namespace Engine
{
    // view
    IRenderableComponent::IRenderableComponent(GameObject& obj, view::Layer layer)
        : IComponent(obj)
        , m_layer(layer)
    {
	};	
	
	void IRenderableComponent::OnCreate()
	{
		ViewManager::Get().RegisterComponent(this);
	}

	IRenderableComponent::~IRenderableComponent()
	{
		ViewManager::Get().UnregisterComponent(this);
	}


	void IComponent::Activate()
	{
		if (!m_isActive)
		{
			m_isActive = true;
			VirtualOnActivated();
		}
	}

	void IComponent::Deactivate()
	{
		if (m_isActive)
		{
			m_isActive = false;
			VirtualOnDeactivated();
		}
	}

};