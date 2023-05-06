#pragma once
#include "../Core/IComponent.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{
	struct SpriteDrawableDef
	{
		const char* TextureName;
		const char* ShaderName;
		view::Layer Layer;
		math::Vec2 Size = {1.0f, 1.0f}; // in world coords
		sf::Color Color = { 255, 255, 255, 255 };
	};

	class SpriteDrawableComponent : public IDrawableComponent
	{
	public:
		SpriteDrawableComponent(GameObject& obj, SpriteDrawableDef def);
		~SpriteDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;

		void SetFlipX(bool flip);
		void SetFlipY(bool flip);
	protected:

	private:
		sf::Vector2f m_desiredPixelSize;
		sf::Sprite m_sprite;
		std::shared_ptr<sf::Texture> m_texture;
	};
}