#pragma once
#include "../Core.h"
#include "../../View/Renderables.h"
#include "../../Core/GameObject.h"

namespace Engine
{
	// used to initialize ShapeViewComponent
	struct ShapeViewDef
	{
		// default is relative to owner's transform
		bool UseAbsoluteTransform = false;

		math::Vec2 Position		= {0.0f, 0.0f};
		float	   Rotation		= 0.0f;
		math::Vec2 Scale		= {1.0f, 1.0f};

		sf::Color  Color		= sf::Color::Red;
		float      PointCount	= 3;
		float	   Radius		= 1;
	};

	class ShapeViewComponent : public IRenderableShapeComponent
	{

	public:
		ShapeViewComponent(GameObject& obj, int zIndex, const ShapeViewDef& def);
		~ShapeViewComponent() override;
		
		void OnCreate() override;
		void Update(float dt) override;
		void OnCollisionStart(GameObject& other) override { m_renderable.shape.Color = sf::Color::Red; };
		void OnCollisionEnd(GameObject& other) override { m_renderable.shape.Color = sf::Color::White; };
	private:
		bool m_useAbsoluteTransform = false;
		Transform m_localTransform;
	};
}