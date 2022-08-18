#include "WorldTransform.h"

namespace Engine
{

	WorldTransform::WorldTransform(GameObject& obj, ITransform::Type type)
		: ITransform(obj, type)
	{

	}

	math::Vec2 WorldTransform::GetPosition() const
	{
		return { 0.0f, 0.0f };
	}

	void WorldTransform::SetRotationDeg(float rotation)
	{
		
	}

	void WorldTransform::SetRotationRad(float rotation)
	{
	
	}

	math::Vec2 WorldTransform::Forward() const
	{
		auto modifiedRotation = m_rotation + (math::M_PI_F / 2);
		return { cosf(modifiedRotation), sinf(modifiedRotation) };
	}

}