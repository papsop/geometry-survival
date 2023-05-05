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
		NotifyTransformChanged();
	}

	math::Vec2 Transform::GetPosition() const
	{ 
		if (GetPositionType() == ITransform::PositionType::Relative && m_parent != nullptr)
			return m_parent->GetTransform()->GetPosition() + m_position;

		return m_position;
	}

	// ===========
	// Rotation
	// ===========
	void Transform::SetRotationDeg(float rotation)
	{
		m_rotation = math::DEG_TO_RAD(rotation);
		NotifyTransformChanged();
	}

	void Transform::SetRotationRad(float rotation)
	{
		m_rotation = rotation;
		NotifyTransformChanged();
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
		result.Scale	= { 1.0f, 1.0f };
		result.Space	= GetPositionSpace();
		return result;
	}

	Transform& Transform::operator=(const Transform& rhs)
	{
		this->m_position = rhs.GetPosition();
		this->m_rotation = rhs.GetRotation();
		return *this;
	}

	void Transform::Debug(view::IViewStrategy* viewStrategy)
	{
		sf::Color color;
		if (GetPositionSpace() == PositionSpace::CameraSpace)
			color = sf::Color::Cyan;
		else
			color = sf::Color::Magenta;

		// Debug position + rotation
		viewStrategy->DebugRenderRectangle(GetPositionSpace(), GetPosition(), { .2f, 0.2f }, GetRotation(), color, color);
		// Debug forward vector
		auto forward = Forward();
		forward *= 2;
		forward += GetPosition();
		viewStrategy->DebugRenderLine(GetPositionSpace(), GetPosition(), forward, color);
	}

	void Transform::SetScale(math::Vec2 scale)
	{
		m_scale = scale;
	}

}