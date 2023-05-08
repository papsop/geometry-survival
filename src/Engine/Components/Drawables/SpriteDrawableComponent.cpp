#include "SpriteDrawableComponent.h"
#include "../../Managers/RenderManager.h"
#include "../../Managers/ResourceManager.h"

namespace Engine
{

	SpriteDrawableComponent::SpriteDrawableComponent(GameObject& obj, SpriteDrawableDef def)
		: IDrawableComponent(obj, def.Layer)
		, m_sprite()
		, m_texture()
	{
		m_texture = ResourceManager::Get().GetTexture(def.TextureName);
		if (def.ShaderName != nullptr)
		{
			m_shader = ResourceManager::Get().GetShader(def.ShaderName);
		}
		
		m_sprite.setTexture(*m_texture);
		m_sprite.setColor(def.Color);

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
		sf::Drawable* drawable = GetDrawableDataForRendering(Owner.GetTransform()->GetAbsoluteTransform(), &m_sprite);
		DrawableData data{ drawable, m_shader.get()};
		drawables[GetLayerAsIndex()].push_back(data);
	}

	void SpriteDrawableComponent::SetFlipX(bool flip)
	{
		auto scale = m_sprite.getScale();
		m_sprite.setScale((flip) ? -scale.x : scale.x, scale.y);
	}

	void SpriteDrawableComponent::SetFlipY(bool flip)
	{
		auto scale = m_sprite.getScale();
		m_sprite.setScale(scale.x, (flip) ? -scale.y : scale.y);
	}

}