#pragma once
#include "../Core/IComponent.h"

#include <SFML/Graphics.hpp>
namespace Engine
{
	struct SpriteDrawableDef
	{
		const char* TexturePath;
		view::Layer Layer;
		math::Vec2 Size = {1.0f, 1.0f}; // in world coords
	};

	class SpriteDrawableComponent : public IDrawableComponent
	{
	public:
		SpriteDrawableComponent(GameObject& obj, SpriteDrawableDef def);
		~SpriteDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;

	protected:

	private:
		sf::Vector2f m_desiredPixelSize;
		sf::Sprite m_sprite;
		sf::Texture m_texture;
	};
}