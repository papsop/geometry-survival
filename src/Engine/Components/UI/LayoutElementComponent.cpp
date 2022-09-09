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

		// reset rect transform to get it ready for the layouter
		m_parentRectTransform->SetPositionType(ITransform::PositionType::Relative);
		m_parentRectTransform->SetAnchor(RectAnchor::TopLeft);
		m_parentRectTransform->SetPosition({ 0.0f, 0.0f });
		
	}

	void LayoutElementComponent::SetSize(math::Vec2 size)
	{
		m_parentRectTransform->SetSize(size);
	}

	void LayoutElementComponent::SetPosition(math::Vec2 pos)
	{
		m_parentRectTransform->SetPosition(pos);
	}

};