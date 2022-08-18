#pragma once
#include "../../Utils/VectorUtils.h"

namespace Engine
{
	
	class GameObject;

	class ITransform
	{
	public:
		enum class Type
		{
			Absolute,
			Relative
		};

		ITransform(GameObject& owner, Type type)
			: m_owner(owner)
			, m_type(type)
			{};

		virtual ~ITransform() = default;

		virtual math::Vec2 GetPosition() const = 0;
		virtual void SetRotationDeg(float rotation) = 0;
		virtual void SetRotationRad(float rotation) = 0;

		virtual math::Vec2 Forward() const = 0;
	protected:
		GameObject& m_owner;
		Type m_type;
	};
}