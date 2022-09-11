#pragma once
#include <memory>

namespace Engine
{
	
	// =========================
	// INTERFACE
	// =========================
	class IConstraint
	{
	public:
		IConstraint() = default;
		virtual ~IConstraint() = default;

		virtual float CalculateValue(float context) = 0;
	};
	using ptr_Constraint = std::unique_ptr<IConstraint>;

	// =========================
	// Constraints
	// =========================

	// =============== CENTERING ===============
	class CenterConstraint final : public IConstraint
	{
	public:
		CenterConstraint() = default;
		~CenterConstraint() = default;

		float CalculateValue(float context) override;
	};

	// =============== ABSOLUTE PIXEL ===============
	class PixelConstraint final : public IConstraint
	{
	public:
		PixelConstraint(float value)
			: m_value(value) {};
		~PixelConstraint() = default;

		float CalculateValue(float context) override;
	private:
		float m_value;
	};

	// =============== RELATIVE FLOAT ===============
	class RelativeConstraint final : public IConstraint
	{
	public:
		RelativeConstraint(float value)
			: m_value(value) {};
		~RelativeConstraint() = default;

		float CalculateValue(float context) override;
	private:
		float m_value;
	};
}