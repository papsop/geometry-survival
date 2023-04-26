#include "SpriteDrawableComponent.h"

namespace Engine
{

	SpriteDrawableComponent::SpriteDrawableComponent(GameObject& obj, view::Layer layer)
		: IDrawableComponent(obj, layer)
		, m_sprite()
		, m_texture()
	{
		m_texture.loadFromFile("assets/sprites/player.png");

		m_sprite.setTexture(m_texture);
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
		m_sprite.setScale(0.5f, 0.5f);
		auto localBounds = m_sprite.getLocalBounds();
		m_sprite.setOrigin(localBounds.width/2, localBounds.height/2);
	}

	void SpriteDrawableComponent::Update(float dt)
	{

	}

	void SpriteDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		drawables.insert({ GetLayer(), {Owner.GetTransform()->GetAbsoluteTransform(), &m_sprite} });
	}

}