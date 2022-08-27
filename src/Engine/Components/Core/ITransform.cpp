#include "ITransform.h"

namespace Engine
{

	ITransform::ITransform(GameObject& owner, const TransformDefinition& def)
		: m_owner(owner)
		, m_transformType(def.TransType)
		, m_positionType(def.PosType)
		, m_space(def.Space)
	{
		SetParent(def.Parent);
	}

	void ITransform::SetParent(GameObject* parent)
	{
		m_parent = parent;
	}

	void ITransform::SetChild(GameObject* child)
	{
		m_children.emplace_back(child);
	}

}