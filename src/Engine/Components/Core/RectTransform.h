#pragma once
#include "../../Debug/IDebuggable.h"
#include "IConstraint.h"

#include <array>

namespace Engine
{
	// Keep outside of RectTransform because we can't forward declare an inner class/struct
	// It's used in ITransform::TransformDefinition
	enum class RectAnchor
	{
		TopLeft,
		TopCenter,
		TopRight,
		CenterLeft,
		CenterCenter,
		CenterRight,
		BottomLeft,
		BottomCenter,
		BottomRight,
	};

	class RectTransform final : public ITransform, public IDebuggableComponent
	{
	public:
		// ====================================================
		// Helper enums
		// ====================================================
		enum class ConstraintParam // index of m_contraints
		{
			X,
			Y,
			Width,
			Height,

			COUNT, // always last
		};

		// ====================================================
		// Class members
		// ====================================================

		RectTransform(GameObject& owner, const TransformDefinition& def);
		~RectTransform() override = default;

		void SetPosition(math::Vec2 pos) override;
		math::Vec2 GetPosition() const override;
		float GetRotation() const override;

		void SetRotationDeg(float rotation) override;
		void SetRotationRad(float rotation) override;
		math::Vec2 Forward() const override;

		AbsoluteTransform GetAbsoluteTransform() const override;

		RectTransform& operator=(const RectTransform& rhs);


		// ================================
		// RectTransform specific functions
		// ================================ 
		void SetAnchor(RectAnchor anchor) { m_anchor = anchor; };
		void SetSize(math::Vec2 size);
		math::Vec2 GetSize() const;
		sf::FloatRect GetBoundingBox() const;

		template<typename T>
		void SetConstraint(ConstraintParam param, T&& c);

		// ================================
		void Debug(view::IViewStrategy* viewStrategy) override;

		void SetScale(math::Vec2 scale) override;

	private:
		math::Vec2 m_position;
		float	   m_rotation;
		math::Vec2 m_size;
		RectAnchor m_anchor;

		std::array<ptr_Constraint, static_cast<size_t>(ConstraintParam::COUNT)> m_constraints;
	};
}

#include "RectTransform.inl"