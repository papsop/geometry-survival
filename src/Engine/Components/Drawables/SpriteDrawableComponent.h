#pragma once
#include "../Core/IComponent.h"

#include <SFML/Graphics.hpp>
namespace Engine
{
	class SpriteDrawableComponent : public IDrawableComponent
	{
	public:
		SpriteDrawableComponent(GameObject& obj, view::Layer layer);
		~SpriteDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;

	protected:

	private:
		sf::Sprite m_sprite;
		sf::Texture m_texture;
	};
}