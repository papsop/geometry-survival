#include "Transform.h"

namespace Engine
{
	Transform::Transform(GameObject& owner, GameObject* parent, PositionType type, PositionSpace space)
		: ITransform(owner, parent, type, space)
		, m_rotation(0.0f)
		, m_position({0.0f, 0.0f})
		, m_scale({1.0f, 1.0f})
	{

	}


	// ===========
	// Position
	// ===========

	void Transform::SetPosition(math::Vec2 pos)
	{ // todo absolute/relative
		m_position = pos;
	}

	math::Vec2 Transform::GetPosition() const
	{ // todo absolute/relative
		return m_position;
	}

	// ===========
	// Rotation
	// ===========
	void Transform::SetRotationDeg(float rotation)
	{
		m_rotation = math::DEG_TO_RAD(rotation);
	}

	void Transform::SetRotationRad(float rotation)
	{
		m_rotation = rotation;
	}

	float Transform::GetRotation() const
	{ // todo absolute/relative
		return m_rotation;
	}



	Engine::math::Vec2 Transform::Forward() const
	{
		auto modifiedRotation = GetRotation() + (math::M_PI_F / 2);
		return { cosf(modifiedRotation), sinf(modifiedRotation) };
	}

	ITransform::AbsoluteTransform Transform::GetAbsoluteTransform() const
	{
		ITransform::AbsoluteTransform result;
		result.Position = GetPosition();
		result.Rotation = GetRotation();
		result.Scale	= { 0.0f, 0.0f };
		result.Space	= GetPositionSpace();
		return result;
	}

	Transform& Transform::operator=(const Transform& rhs)
	{
		this->m_position = rhs.GetPosition();
		this->m_rotation = rhs.GetRotation();
		return *this;
	}

}