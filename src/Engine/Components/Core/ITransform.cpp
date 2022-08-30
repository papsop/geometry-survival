#include "ITransform.h"
#include "../../Core/GameObject/GameObject.h"
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

	void ITransform::SetPositionType(PositionType posType)
	{
		m_positionType = posType;
	}

	void ITransform::NotifyTransformChanged()
	{
		m_owner.SendMessageTo(&m_owner, MessageType::Transform_Changed);
	}

}