#pragma once
#include "ITransform.h"

namespace Engine
{
	class Transform final : public ITransform
	{
	public:
		Transform(GameObject& owner, const TransformDefinition& def);
		~Transform() override = default;

		void SetPosition(math::Vec2 pos) override;
		math::Vec2 GetPosition() const override;
		float GetRotation() const override;

		void SetRotationDeg(float rotation) override;
		void SetRotationRad(float rotation) override;
		math::Vec2 Forward() const override;

		AbsoluteTransform GetAbsoluteTransform() const override;

		Transform& operator=(const Transform& rhs);
	private:
		math::Vec2 m_position;
		math::Vec2 m_scale;
		float m_rotation;
	};
}