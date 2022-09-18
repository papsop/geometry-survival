#pragma once
#include "../Core.h"

namespace Engine
{
  // used to initialize TextViewComponent
  struct TextViewDef
  {
    sf::Color			Color         = sf::Color::White;
    unsigned int	FontSize      = 16;
    const char*		Text          = "empty";
    view::Layer		Layer         = view::Layer::UI;
    bool          ShouldCenter  = true;
  };

  class TextViewComponent : public IRenderableComponent
  {
  public:
    TextViewComponent(GameObject& obj, const TextViewDef& def);
    ~TextViewComponent() override = default;

    view::Renderable GetRenderable() override;
    view::Renderable& GetMutableRenderable() override;

    void SetText(std::string text);
  private:
    view::Renderable m_renderable;
    std::string m_text;
  };
};