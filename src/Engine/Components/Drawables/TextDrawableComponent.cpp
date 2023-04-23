#include "TextDrawableComponent.h"
#include "../../Managers/RenderManager.h"

namespace Engine
{

	TextDrawableComponent::TextDrawableComponent(GameObject& obj, view::Layer layer)
		: IDrawableComponent(obj, layer)
		, m_text()
	{
		m_text.setString("test");
		m_text.setFont(RenderManager::Get().GetFont());
		m_text.setCharacterSize(16);
		m_text.setFillColor(sf::Color::Yellow);
		// center text, need to do it after setting font
		sf::FloatRect textRect = m_text.getLocalBounds();
		m_text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	}

	void TextDrawableComponent::Update(float dt)
	{

	}

	void TextDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		drawables.insert({ GetLayer(), {Owner.GetTransform()->GetAbsoluteTransform(), &m_text} });
	}

}