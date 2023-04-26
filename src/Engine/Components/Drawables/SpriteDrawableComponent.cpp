#include "SpriteDrawableComponent.h"

namespace Engine
{

	SpriteDrawableComponent::SpriteDrawableComponent(GameObject& obj, SpriteDrawableDef def)
		: IDrawableComponent(obj, def.Layer)
		, m_sprite()
		, m_texture()
	{
		m_texture.loadFromFile(def.TexturePath);

		m_sprite.setTexture(m_texture);
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
		m_sprite.setScale(1.0f, 1.0f);
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