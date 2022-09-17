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
		sf::Color		Color				= sf::Color::Red;
		float				PointCount	= 3;
		float				Radius			= 1;

		view::Layer Layer		= view::Layer::BACKGROUND;
	};

	class ShapeViewComponent : public IRenderableComponent
	{

	public:
		ShapeViewComponent(GameObject& obj, const ShapeViewDef& def);
		~ShapeViewComponent() override = default;
		
		view::Renderable GetRenderable() override;
		view::Renderable& GetMutableRenderable() override;

	private:
		view::Renderable m_renderable;
	};
}