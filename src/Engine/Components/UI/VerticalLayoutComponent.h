#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{
	class VerticalLayoutComponent : public IComponent
	{
	public:
		VerticalLayoutComponent(GameObject& obj);
		~VerticalLayoutComponent();


		void VirtualOnCreate() override;
		void Update(float dt) override;

	private:
		RectTransform* m_parentRectTransform = nullptr;
	};
};