#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"
namespace Engine
{
	class LayoutElementComponent : public IComponent
	{
	public:
		LayoutElementComponent(GameObject& obj);
		~LayoutElementComponent() = default;

		void VirtualOnCreate() override;

		// Layout element specific
		void SetSize(math::Vec2 size);
		void SetPosition(math::Vec2 pos);

	private:
		RectTransform* m_parentRectTransform = nullptr;
	};
};