#include "UIElement.h"

namespace Engine
{
	namespace ui
	{
		UIElement::UIElement(UIAnchor anchor, bool isPosAbsolute, math::Vec2 anchorPosition, math::Vec2 size)
			: m_anchor(anchor)
			, m_isPosAbsolute(isPosAbsolute)
			, m_anchorPos(anchorPosition)
			, m_size(size)
		{

		}

	}
}