#pragma once
#include "../Core/IComponent.h"

namespace Engine
{

	struct TextDrawableDef
	{
		std::string Value = "Empty";
		size_t CharacterSize = 16;
		sf::Color Color = sf::Color::White;
		view::Layer Layer = view::Layer::BACKGROUND;
	};

	class TextDrawableComponent : public IDrawableComponent
	{
	public:
		TextDrawableComponent(GameObject& obj, TextDrawableDef def);
		~TextDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;

		void SetString(const char* val);
		void SetString(std::string val);
		void SetCharacterSize(size_t val);
		void SetColor(sf::Color val);
	protected:

	private:
		std::string m_textValue; // holds c_str() for text component
		sf::Text m_text;
	};
}