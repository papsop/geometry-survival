#pragma once
#include "../Core/IComponent.h"

namespace Engine
{
	class TextDrawableComponent : public IDrawableComponent
	{
	public:
		TextDrawableComponent(GameObject& obj, view::Layer layer);
		~TextDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;
	protected:

	private:
		sf::Text m_text;
	};
}