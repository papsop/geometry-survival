#include "RectangleViewComponent.h"

namespace Engine
{


	RectangleViewComponent::RectangleViewComponent(GameObject& obj, const RectangleViewDef& def)
		: IRenderableComponent(obj, def.Layer)
	{
	}

};