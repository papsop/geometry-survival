#include "TextViewComponent.h"

namespace Engine
{

  TextViewComponent::TextViewComponent(GameObject& obj, const TextViewDef& def)
    : IRenderableComponent(obj, def.Layer)
    , m_renderable(view::Renderable::RenderableType::TEXT)
  {
    m_renderable.text.Color = def.Color;
    m_renderable.text.Size = def.FontSize;
    m_renderable.text.Value = def.Text;
    m_renderable.text.ShouldCenter = def.ShouldCenter;
  }

  void TextViewComponent::SetText(std::string text)
  {
    m_text = text;
  }

  view::Renderable TextViewComponent::GetRenderable()
  {
    m_renderable.Transform = Owner.GetTransform()->GetAbsoluteTransform();
    m_renderable.text.Value = m_text.c_str();
    return m_renderable;
  }

  view::Renderable& TextViewComponent::GetMutableRenderable()
  {
    return m_renderable;
  }

};
