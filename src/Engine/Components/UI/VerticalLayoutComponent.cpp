#include "VerticalLayoutComponent.h"
#include "LayoutElementComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	VerticalLayoutComponent::VerticalLayoutComponent(GameObject& obj)
		: IComponent(obj)
	{

	}

	void VerticalLayoutComponent::OnCreate()
	{
		m_parentRectTransform = dynamic_cast<RectTransform*>(Owner.GetTransform());
		DD_ASSERT(m_parentRectTransform != nullptr, "HorizontalLayoutComponent only usable with a RectTransform");

		ComponentManager::Get().RegisterComponent(this);
	}

	VerticalLayoutComponent::~VerticalLayoutComponent()
	{
		ComponentManager::Get().UnregisterComponent(this);
	}

	void VerticalLayoutComponent::Update(float dt)
	{
		auto children = m_parentRectTransform->GetChildren();
		size_t count = children.size();
		float child_size_y = m_parentRectTransform->GetSize().y / count;
		size_t index = 0;

		for (auto& child : children)
		{
			auto layoutElement = child->GetComponent<LayoutElementComponent>();
			if (layoutElement)
			{
				layoutElement->SetPosition({0.0f, index * child_size_y});
				layoutElement->SetSize({m_parentRectTransform->GetSize().x, child_size_y});
			}
			++index;
		}
	}

};