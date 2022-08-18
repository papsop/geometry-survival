#pragma once
#include "ITransform.h"

namespace Engine
{
	class ScreenTransform final : public ITransform
	{
	public:
		ScreenTransform(GameObject& owner, ITransform::Type type);
		~ScreenTransform() override = default;

		math::Vec2 GetPosition() const override;
		void SetRotationDeg(float rotation);
		void SetRotationRad(float rotation);
		math::Vec2 Forward() const override;

		// ITransform holds a reference to the owner GameObject, so we can't return a new object on operator+.
		// Use operator+= instead, and only add rhs Pos/Rot/Scale to lhs (keep lhs reference)
		ScreenTransform& operator+=(const ScreenTransform& rhs);
		bool operator==(const ScreenTransform& rhs) const;
		bool operator!=(const ScreenTransform& rhs) const;
	private:
		math::Vec2 m_position;
	};
}