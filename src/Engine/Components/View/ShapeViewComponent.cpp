#include "ShapeViewComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	ShapeViewComponent::ShapeViewComponent(GameObject& obj, const ShapeViewDef& def)
		: IRenderableComponent(obj, def.Layer)
		, m_renderable(view::Renderable::RenderableType::SHAPE)
	{
		m_renderable.shape.Color = def.Color;
		m_renderable.shape.PointCount = def.PointCount;
		m_renderable.shape.Radius = def.Radius;
	}

	view::Renderable& ShapeViewComponent::GetMutableRenderable()
	{
		return m_renderable;
	}

	view::Renderable ShapeViewComponent::GetRenderable()
	{
		m_renderable.Transform = Owner.GetTransform()->GetAbsoluteTransform();
		return m_renderable;
	}

}

