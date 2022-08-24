#pragma once
#include "../../Utils/VectorUtils.h"
#include <list>

namespace Engine
{
	
	class GameObject;

	class ITransform
	{
	public:

		// ====================================================================================
		// Helper declarations
		// ====================================================================================
		enum class PositionType
		{
			Absolute,
			Relative
		};

		enum class PositionSpace
		{
			WorldSpace,
			CameraSpace				// relative to the current camera view
		};

		// Used when we want to export ITransform into movable form without Owner/parent/children
		// AbsoluteTransform has already calculated relativeness to parent
		struct AbsoluteTransform
		{
			math::Vec2		Position;
			float			Rotation;
			math::Vec2		Scale;
			PositionSpace	Space;

			AbsoluteTransform operator=(const AbsoluteTransform& rhs)
			{
				this->Position	= rhs.Position;
				this->Rotation	= rhs.Rotation;
				this->Scale		= rhs.Scale;
				this->Space		= rhs.Space;
				return *this;
			}
		};

		// Used to Initialize GameObject's transform
		struct TransformDefinition
		{
			math::Vec2		Position = {0.0f, 0.0f};
			float			Rotation = 0.0f;
			math::Vec2		Scale = {1.0f, 1.0f};
			PositionSpace	Space = PositionSpace::WorldSpace;
			PositionType	Type = PositionType::Absolute;

			GameObject*		Parent = nullptr;
		};
		// ====================================================================================
		// Class members
		// ====================================================================================

		ITransform(GameObject& owner, const TransformDefinition& def);

		virtual ~ITransform() = default;

		virtual void SetPosition(math::Vec2 pos) = 0;
		virtual math::Vec2 GetPosition() const = 0;
		virtual float GetRotation() const = 0;

		virtual void SetRotationDeg(float rotation) = 0;
		virtual void SetRotationRad(float rotation) = 0;

		virtual math::Vec2 Forward() const = 0;
		virtual AbsoluteTransform GetAbsoluteTransform() const = 0;


		PositionType GetPositionType() const { return m_type; };
		PositionSpace GetPositionSpace() const { return m_space; };
		GameObject& GetOwner() const { return m_owner; };
		GameObject* GetParent() const { return m_parent; };
		const std::list<GameObject*>& GetChildren() const { return m_children; };

		void SetParent(GameObject* parent);
		void SetChild(GameObject* child);

	protected:
		GameObject& m_owner;
		PositionType m_type;
		PositionSpace m_space;

		// Transform hierarchy
		// If my parent dies - I kill myself and all my children
		// ^ that sounds awful
		GameObject* m_parent = nullptr;
		std::list<GameObject*> m_children;	// list seems fine right now, might change to vector

	};
}