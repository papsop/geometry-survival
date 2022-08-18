#include "ScreenTransform.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{

	ScreenTransform::ScreenTransform(GameObject& owner, ITransform::Type type)
		: ITransform(owner, type)
	{

	}

	math::Vec2 ScreenTransform::GetPosition() const
	{
		if (m_type == ITransform::Type::Absolute)
		{
			return m_position;
		}
		else
		{
			return m_position; // TODO: OWNER POSITION
		}
	}

	void ScreenTransform::SetRotationDeg(float rotation)
	{

	}

	void ScreenTransform::SetRotationRad(float rotation)
	{

	}

	math::Vec2 ScreenTransform::Forward() const
	{
		return { 0.0f, 0.0f };
	}
	 
	ScreenTransform& ScreenTransform::operator+=(const ScreenTransform& rhs)
	{
		this->m_position = this->GetPosition() + rhs.GetPosition();

		return *this;
	}

	bool ScreenTransform::operator!=(const ScreenTransform& rhs) const
	{
		return !(*this == rhs);
	}

	bool ScreenTransform::operator==(const ScreenTransform& rhs) const
	{
		return true;
	}

}