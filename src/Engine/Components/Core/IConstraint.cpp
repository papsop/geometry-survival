#include "IConstraint.h"

namespace Engine
{
	namespace constraints
	{
		float CenterConstraint::CalculateValue(float context)
		{ // should receive width/height as context
			return context/2.0f;
		}

		float RelativeConstraint::CalculateValue(float context)
		{ // should receive width/height as context
			return context * m_value;
		}

		float PixelConstraint::CalculateValue(float context)
		{ // context is irrelevant
			return m_value;
		}

	}
}