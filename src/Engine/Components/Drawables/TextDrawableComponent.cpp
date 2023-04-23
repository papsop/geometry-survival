#include "TextDrawableComponent.h"
#include "../../Managers/RenderManager.h"
#include <string>

namespace Engine
{

	TextDrawableComponent::TextDrawableComponent(GameObject& obj, TextDrawableDef def)
		: IDrawableComponent(obj, def.Layer)
		, m_text()
	{
		m_text.setFont(RenderManager::Get().GetFont());

		SetString(def.Value);
		SetCharacterSize(def.CharacterSize);
		SetColor(def.Color);
	}

	void TextDrawableComponent::Update(float dt)
	{

	}

	void TextDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		drawables.insert({ GetLayer(), {Owner.GetTransform()->GetAbsoluteTransform(), &m_text} });
	}

	void TextDrawableComponent::SetString(const char* val)
	{
		m_textValue = val;
		m_text.setString(m_textValue.c_str());
	}

	void TextDrawableComponent::SetString(std::string val)
	{
		m_textValue = val;
		m_text.setString(m_textValue.c_str());
	}

	void TextDrawableComponent::SetCharacterSize(size_t val)
	{
		m_text.setCharacterSize(val);
		sf::FloatRect textRect = m_text.getLocalBounds();
		m_text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	}

	void TextDrawableComponent::SetColor(sf::Color val)
	{
		m_text.setColor(val);
	}

}