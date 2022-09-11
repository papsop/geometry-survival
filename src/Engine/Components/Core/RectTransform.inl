#include "RectTransform.h"

namespace Engine
{
	template<typename T>
	void RectTransform::SetConstraint(ConstraintParam param, T&& c)
	{
		m_constraints[static_cast<size_t>(param)] = std::make_unique<T>(c);
	}
}