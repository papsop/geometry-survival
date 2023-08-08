#pragma once
#include "../Core/IComponent.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{
	struct SpriteDrawableDef
	{
		const char* TextureName;
		const char* ShaderName = nullptr;
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

		void FlipX();
		void FlipY();
		void SetSize(math::Vec2 size);
		void UpdateSize();
		void SetTexture(const char* textureName);
		void SetTextureRect(sf::IntRect rect);

    template<
      typename T,
      typename ... Args,
      typename = enable_if_base_of_component<T>
    >
      void AddComponent(Args&& ... args);

		template<typename ... Args>
		void SetShaderParameter(const char* parameter, Args&& ... args);
	protected:

	private:
		math::Vec2 m_desiredWorldSize;
		sf::Vector2f m_desiredPixelSize;
		sf::Sprite m_sprite;
		sf::Color m_color;
		std::shared_ptr<sf::Texture> m_texture;
		std::shared_ptr<sf::Shader> m_shader;
	};

}

#include "SpriteDrawableComponent.inl"