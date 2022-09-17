#include "RectangleViewComponent.h"

namespace Engine
{

	RectangleViewComponent::RectangleViewComponent(GameObject& obj, const RectangleViewDef& def)
		: IRenderableComponent(obj, def.Layer)
    , m_renderable(view::Renderable::RenderableType::RECTANGLE)
	{
    m_renderable.rectangle.FillColor = def.Color;
    m_renderable.rectangle.Size = def.Size;
	}

  Engine::view::Renderable& RectangleViewComponent::GetMutableRenderable()
  {
    return m_renderable;
  }

  Engine::view::Renderable RectangleViewComponent::GetRenderable()
  {
    if (auto* ownerRectTrans = Owner.GetTransformAs<Engine::RectTransform>())
    {
      m_renderable.rectangle.Size = ownerRectTrans->GetSize();
    }
    m_renderable.Transform = Owner.GetTransform()->GetAbsoluteTransform();

    return m_renderable;
  }
};