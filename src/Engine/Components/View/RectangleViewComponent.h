#pragma once
#include "../Core.h"
#include "../../View/Renderables.h"
#include "../../Core/GameObject.h"

namespace Engine
{
	// used to initialize RectangleViewComponent
	struct RectangleViewDef
	{
		// default is relative to owner's transform
		bool UseAbsoluteTransform = false;

		math::Vec2 Position = { 0.0f, 0.0f };
		float	   Rotation = 0.0f;
		math::Vec2 Scale = { 1.0f, 1.0f };

		sf::Color  Color = sf::Color::Red;
		float      PointCount = 3;
		float	   Radius = 1;
	};

	class RectangleViewComponent : public IRenderableShapeComponent
	{
	};
}