#include "Transform.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{
	Transform::Transform(GameObject& owner, const TransformDefinition& def)
		: ITransform(owner, def)
		, m_rotation(def.Rotation)
		, m_position(def.Position)
		, m_scale(def.Scale)
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
	{ 
		if (m_type == ITransform::PositionType::Relative && m_parent != nullptr)
			return m_parent->GetTransform()->GetPosition() + m_position;

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