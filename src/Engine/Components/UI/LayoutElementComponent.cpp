#include "LayoutElementComponent.h"

namespace Engine
{

	LayoutElementComponent::LayoutElementComponent(GameObject& obj)
		: IComponent(obj)
	{

	}

	void LayoutElementComponent::OnCreate()
	{
		m_parentRectTransform = dynamic_cast<RectTransform*>(Owner.GetTransform());
		DD_ASSERT(m_parentRectTransform != nullptr, "LayoutElementComponent only usable with a RectTransform");
	}

};