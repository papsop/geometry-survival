#pragma once
#include "../Core.h"
#include "../../View/Renderables.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{
	// used to initialize RectangleViewComponent
	struct RectangleViewDef
	{
		// default is relative to owner's transform
		bool			UseAbsoluteTransform = false;

		math::Vec2		Position = { 0.0f, 0.0f };
		float			Rotation = 0.0f;
		math::Vec2		Scale = { 1.0f, 1.0f };

		sf::Color		Color = sf::Color::Red;
		math::Vec2		Size = {2.0f, 1.0f};
	};

	class RectangleViewComponent : public IRenderableShapeComponent
	{
	public:
		RectangleViewComponent(GameObject& obj, int zIndex, const RectangleViewDef& def);
		~RectangleViewComponent() override;
		void OnCreate() override;
		void Update(float dt) override;
		void OnCollisionStart(GameObject* other) override;
	private:
		bool m_useAbsoluteTransform = false;
		Transform m_localTransform;
	};
}