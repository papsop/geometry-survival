#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{
	class HorizontalLayoutComponent : public IComponent
	{
	public:
		HorizontalLayoutComponent(GameObject& obj);
		~HorizontalLayoutComponent() = default;


		void OnCreate() override;

	private:
		RectTransform* m_parentRectTransform = nullptr;
	};
};