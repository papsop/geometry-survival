#include "SpriteDrawableComponent.h"
#include "../../Managers/RenderManager.h"
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

		auto localBounds = m_sprite.getLocalBounds();
		m_sprite.setOrigin(localBounds.width / 2, localBounds.height / 2);
		// Sprite doesn't support setting size by pixels, so use scaling instead
		// this scale is local to the sprite itself and will get multiplied
		// by GameObject's transform.scale before rendering. The size is in world 
		// coordinates (used by box2d) so it's synced with the physics system
		// and PixelsPerMeter still apply to this sprite
		m_desiredPixelSize = RenderManager::Get().coordsToPixels(def.Size);
		sf::Vector2f scale = { m_desiredPixelSize.x / localBounds.width, m_desiredPixelSize.y / localBounds.height };
		m_sprite.setScale(scale);
	}

	void SpriteDrawableComponent::Update(float dt)
	{

	}

	void SpriteDrawableComponent::GetDrawables(TDrawablesMap& drawables)
	{
		drawables.insert({ GetLayer(), {Owner.GetTransform()->GetAbsoluteTransform(), &m_sprite} });
	}

}