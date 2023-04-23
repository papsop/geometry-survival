#pragma once
#include "../Core/IComponent.h"

namespace Engine
{
	class ShapeDrawableComponent : public IDrawableComponent
	{
	public:
		ShapeDrawableComponent(GameObject& obj, view::Layer layer);
		~ShapeDrawableComponent() override = default;

		void Update(float dt) override;

		void GetDrawables(TDrawablesMap& drawables) override;
	protected:

	private:
		sf::CircleShape m_circleShape;
	};
}