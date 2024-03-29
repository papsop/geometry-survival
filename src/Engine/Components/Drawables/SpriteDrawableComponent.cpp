#include "SpriteDrawableComponent.h"
#include "../../Managers/RenderManager.h"
#include "../../Managers/ResourceManager.h"

namespace Engine
{

	SpriteDrawableComponent::SpriteDrawableComponent(GameObject& obj, SpriteDrawableDef def)
		: IDrawableComponent(obj, def.Layer)
		, m_sprite()
		, m_texture()
		, m_desiredWorldSize(def.Size)
		, m_color(def.Color)
	{
		SetTexture(def.TextureName);
		UpdateSize();

		if (def.ShaderName != nullptr)
		{
			m_shader = ResourceManager::Get().GetShader(def.ShaderName);
			SetShaderParameter("texture", sf::Shader::CurrentTexture);
		}
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

	void SpriteDrawableComponent::FlipX()
  {
    auto scale = m_sprite.getScale();
		m_sprite.setScale(-scale.x, scale.y);
	}

	void SpriteDrawableComponent::FlipY()
	{
    auto scale = m_sprite.getScale();
    m_sprite.setScale(scale.x, -scale.y);
	}

	void SpriteDrawableComponent::SetSize(math::Vec2 size)
	{
		m_desiredWorldSize = size;
		UpdateSize();
	}

	void SpriteDrawableComponent::SetTexture(const char* textureName)
	{
		m_texture = ResourceManager::Get().GetTexture(textureName);
		m_sprite.setTexture(*m_texture);
		m_sprite.setColor(m_color);
		UpdateSize();
	}

	sf::Vector2u SpriteDrawableComponent::GetTextureSize()
	{
		if (m_sprite.getTexture() != nullptr)
		{
			return m_sprite.getTexture()->getSize();
		}
		
		return { 0, 0 };
	}

	void SpriteDrawableComponent::SetTextureRect(sf::IntRect rect)
	{
		m_sprite.setTextureRect(rect);
	}

  void SpriteDrawableComponent::UpdateSize()
  {
    // Sprite doesn't support setting size by pixels, so use scaling instead
		// this scale is local to the sprite itself and will get multiplied
		// by GameObject's transform.scale before rendering. The size is in world 
		// coordinates (used by box2d) so it's synced with the physics system
		// and PixelsPerMeter still apply to this sprite
		m_desiredPixelSize = RenderManager::Get().coordsToPixels(m_desiredWorldSize);
    if (m_texture->isRepeated())
    {
      m_sprite.setTextureRect({ 0, 0, static_cast<int>(m_desiredPixelSize.x), static_cast<int>(m_desiredPixelSize.y) });
    }
    auto localBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(localBounds.width / 2, localBounds.height / 2);
    sf::Vector2f scale = { m_desiredPixelSize.x / localBounds.width, m_desiredPixelSize.y / localBounds.height };

		// TODO: make this prettier
		if (m_sprite.getScale().x < 0)
			scale.x *= -1;

    m_sprite.setScale(scale);
  }

}