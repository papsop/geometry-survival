#pragma once
#include "../Core.h"
#include "../../View/Renderables.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{
	// used to initialize RectangleViewComponent
	struct RectangleViewDef
	{
		sf::Color			Color			= sf::Color::Red;
		math::Vec2		Size			= {2.0f, 1.0f};
		view::Layer		Layer			= view::Layer::BACKGROUND;
	};

	class RectangleViewComponent : public IRenderableComponent
	{
	public:
		RectangleViewComponent(GameObject& obj, const RectangleViewDef& def);
		~RectangleViewComponent() = default;

    view::Renderable GetRenderable() override;
    view::Renderable& GetMutableRenderable() override;

  private:
    view::Renderable m_renderable;
	};
}