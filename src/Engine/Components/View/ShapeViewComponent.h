#pragma once
#include "../Core.h"
#include "../../View/Renderables.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/ViewLayers.h"

namespace Engine
{
	// used to initialize ShapeViewComponent
	struct ShapeViewDef
	{
		// default is relative to owner's transform
		bool UseAbsoluteTransform = false;

		math::Vec2 Position		= {0.0f, 0.0f};
		float	   Rotation		= 0.0f;
		math::Vec2 Scale		= {1.0f, 1.0f};

		sf::Color  Color		= sf::Color::Red;
		float      PointCount	= 3;
		float	   Radius		= 1;

		view::Layer Layer			= view::Layer::BACKGROUND;
	};

	class ShapeViewComponent : public IRenderableShapeComponent
	{

	public:
		ShapeViewComponent(GameObject& obj, const ShapeViewDef& def);
		~ShapeViewComponent() override;
		
		void OnCreate() override;
		void Update(float dt) override;
	private:
		bool m_useAbsoluteTransform = false;
		Transform m_localTransform;
	};
}