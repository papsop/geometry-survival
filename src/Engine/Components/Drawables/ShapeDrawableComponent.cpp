#include "ShapeDrawableComponent.h"
#include "../../Managers/RenderManager.h"

namespace Engine
{
	ShapeDrawableComponent::ShapeDrawableComponent(GameObject& obj, ShapeDrawableDef def)
		: IDrawableComponent(obj, def.Layer)
		, m_circleShape()
	{
		auto radius = RenderManager::Get().coordToPixel(def.Radius);

		SetRadius(radius);
		SetColor(def.Color);
		SetPointCount(def.PointCount);
	}

	void ShapeDrawableComponent::Update(float dt)
	{
		
	}

	void ShapeDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		sf::Drawable* drawable = GetDrawableDataForRendering(Owner.GetTransform()->GetAbsoluteTransform(), &m_circleShape);
		DrawableData data{ drawable, nullptr };
		drawables.insert({ GetLayer(), data});
	}

	void ShapeDrawableComponent::SetPointCount(size_t val)
	{
		m_circleShape.setPointCount(val);
	}

	void ShapeDrawableComponent::SetColor(sf::Color val)
	{
		m_circleShape.setFillColor(val);
	}

	void ShapeDrawableComponent::SetRadius(float val)
	{
		m_circleShape.setRadius(val);
		m_circleShape.setOrigin({ val , val });
	}

}