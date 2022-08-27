#include "HorizontalLayoutComponent.h"

namespace Engine
{

	HorizontalLayoutComponent::HorizontalLayoutComponent(GameObject& obj)
		: IComponent(obj)
	{

	}

	void HorizontalLayoutComponent::OnCreate()
	{
		m_parentRectTransform = dynamic_cast<RectTransform*>(Owner.GetTransform());
		DD_ASSERT(m_parentRectTransform != nullptr, "HorizontalLayoutComponent only usable with a RectTransform");
	}

};