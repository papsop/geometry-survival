#pragma once
#include "../Core/IComponent.h"

namespace Engine
{

	struct ShapeDrawableDef
	{
		float Radius = 2.f;
		size_t PointCount = 5;
		sf::Color Color = sf::Color::Red;
		view::Layer Layer = view::Layer::BACKGROUND;
	};
	
	class ShapeDrawableComponent : public IDrawableComponent
	{
	public:
		ShapeDrawableComponent(GameObject& obj, ShapeDrawableDef def);
		~ShapeDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;

		void SetPointCount(size_t val);
		void SetColor(sf::Color val);
		void SetRadius(float val);
	protected:

	private:
		sf::CircleShape m_circleShape;
	};
}