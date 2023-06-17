#include "HorizontalLayoutComponent.h"
#include "LayoutElementComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	HorizontalLayoutComponent::HorizontalLayoutComponent(GameObject& obj)
		: IComponent(obj)
	{

	}

	void HorizontalLayoutComponent::VirtualOnCreate()
{
		m_parentRectTransform = dynamic_cast<RectTransform*>(Owner.GetTransform());
		DD_ASSERT(m_parentRectTransform != nullptr, "HorizontalLayoutComponent only usable with a RectTransform");

		ComponentManager::Get().RegisterComponent(this);
	}

	HorizontalLayoutComponent::~HorizontalLayoutComponent()
	{
		ComponentManager::Get().UnregisterComponent(this);
	}

	void HorizontalLayoutComponent::Update(float dt)
	{
		auto children = m_parentRectTransform->GetChildren();
		size_t count = children.size();
		float child_size_x = m_parentRectTransform->GetSize().x / count;
		size_t index = 0;

		for (auto& child : children)
		{
			auto layoutElement = child->GetComponent<LayoutElementComponent>();
			if (layoutElement)
			{
				layoutElement->SetPosition({ index * child_size_x , 0.0f});
				layoutElement->SetSize({child_size_x, m_parentRectTransform->GetSize().y });
			}
			++index;
		}
	}

};