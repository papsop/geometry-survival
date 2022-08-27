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

		void OnCreate() override;

	private:
		RectTransform* m_parentRectTransform = nullptr;
	};
};