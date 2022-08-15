#pragma once
#include "../Utils/VectorUtils.h"
#include <list>
#include <memory>
namespace Engine
{
	namespace ui
	{
		enum class UIAnchor
		{
			TopLeft, TopCenter, TopRight,
			CenterLeft, CenterCenter, CenterRight,
			BottomLeft, BottomCenter, BottomRight
		};

		class UIElement
		{
		public:
			UIElement(UIAnchor anchor, bool isPosAbsolute, math::Vec2 anchorPosition, math::Vec2 size);

		private:
			UIAnchor m_anchor;
			bool m_isPosAbsolute;
			math::Vec2 m_anchorPos;
			math::Vec2 m_size;

			std::list<std::unique_ptr<UIElement>> m_children;
		};
	}
}