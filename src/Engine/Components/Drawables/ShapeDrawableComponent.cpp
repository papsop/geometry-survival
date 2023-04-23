#include "ShapeDrawableComponent.h"
#include "../../Managers/RenderManager.h"

namespace Engine
{
	ShapeDrawableComponent::ShapeDrawableComponent(GameObject& obj, view::Layer layer)
		: IDrawableComponent(obj, layer)
		, m_circleShape()
	{
		auto radius = RenderManager::Get().coordToPixel(2.0f);

		m_circleShape.setFillColor(sf::Color::Red);
		m_circleShape.setPointCount(3);
		m_circleShape.setRadius(radius);
		m_circleShape.setOrigin({radius , radius});
	}

	void ShapeDrawableComponent::Update(float dt)
	{
		
	}

	void ShapeDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		drawables.insert({ GetLayer(), {Owner.GetTransform()->GetAbsoluteTransform(), &m_circleShape}});
	}

}