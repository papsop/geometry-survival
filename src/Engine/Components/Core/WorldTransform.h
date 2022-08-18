#pragma once
#include "ITransform.h"

namespace Engine
{
	class WorldTransform final : public ITransform
	{
	public:
		WorldTransform(GameObject& obj, ITransform::Type type);
		~WorldTransform() override = default;

		math::Vec2 GetPosition() const override;
		void SetRotationDeg(float rotation) override;
		void SetRotationRad(float rotation) override;
		math::Vec2 Forward() const override;

	private:
		math::Vec2 m_position;
		math::Vec2 m_scale;
		float m_rotation;
	};
}