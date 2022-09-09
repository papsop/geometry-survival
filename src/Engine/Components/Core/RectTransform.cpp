#include "RectTransform.h"
#include "../../Core/GameObject/GameObject.h"

namespace Engine
{

	RectTransform::RectTransform(GameObject& owner, const TransformDefinition& def)
		: ITransform(owner, def)
		, m_position(def.Position)
		, m_rotation(def.Rotation)
		, m_size(def.Size)
		, m_anchor(def.Anchor)
	{

	}

	void RectTransform::SetPosition(math::Vec2 pos)
	{
		m_position = pos;
		m_owner.SendMessageTo(&m_owner, MessageType::Transform_Changed);
	}

	math::Vec2 RectTransform::GetPosition() const
	{
		// Calculate relative position
		math::Vec2 parentPos = { 0.0f, 0.0f };
		if (m_positionType == ITransform::PositionType::Relative && m_parent != nullptr)
		{
			auto parentRect = dynamic_cast<RectTransform*>(m_parent->GetTransform());
			if (parentRect)
			{
				auto parentBB = parentRect->GetBoundingBox();
				parentPos = { parentBB.left, parentBB.top };
			}
			else
				LOG_WARN("[GameObject '%d'] RectTransform's parent isn't a RectTransform - not allowed.", m_owner.DebugName);
		}
			

		return m_position + parentPos;
	}

	float RectTransform::GetRotation() const
	{
		return 0.0f;
	}

	void RectTransform::SetRotationDeg(float rotation)
	{
		m_rotation = math::DEG_TO_RAD(rotation);
		NotifyTransformChanged();
	}

	void RectTransform::SetRotationRad(float rotation)
	{
		m_rotation = rotation;
		NotifyTransformChanged();
	}

	math::Vec2 RectTransform::Forward() const
	{ // doesn't make sense in rectTransform
		return { 0.0f, 0.0f };
	}

	ITransform::AbsoluteTransform RectTransform::GetAbsoluteTransform() const
	{
		ITransform::AbsoluteTransform result;
		result.Position = GetPosition();
		result.Rotation = GetRotation();
		result.Scale = { 1.0f, 1.0f };
		result.Space = GetPositionSpace();
		return result;
	}

	void RectTransform::SetSize(math::Vec2 size)
	{
		m_size = size;
		NotifyTransformChanged();
	}

	Engine::math::Vec2 RectTransform::GetSize()
	{
		return m_size;
	}

	sf::FloatRect RectTransform::GetBoundingBox() const
	{
		sf::FloatRect result;
		math::Vec2 position = GetPosition();
		if (m_anchor == RectAnchor::TopLeft)
		{
			result.left		= position.x;
			result.top		= position.y;
		}
		else if (m_anchor == RectAnchor::TopCenter)
		{
			result.left		= position.x - (m_size.x/2);
			result.top		= position.y;
		}
		else if (m_anchor == RectAnchor::TopRight)
		{
			result.left		= position.x - m_size.x;
			result.top		= position.y;
		}
		else if (m_anchor == RectAnchor::CenterLeft)
		{
			result.left		= position.x;
			result.top		= position.y - (m_size.y / 2);
		}
		else if (m_anchor == RectAnchor::CenterCenter)
		{
			result.left		= position.x - (m_size.x/2);
			result.top		= position.y - (m_size.y/2);
		}
		else if (m_anchor == RectAnchor::CenterRight)
		{
			result.left		= position.x - m_size.x;
			result.top		= position.y - (m_size.y / 2);
		}
		else if (m_anchor == RectAnchor::BottomLeft)
		{
			result.left		= position.x;
			result.top		= position.y - m_size.y;
		}
		else if (m_anchor == RectAnchor::BottomCenter)
		{
			result.left		= position.x - (m_size.x/2);
			result.top		= position.y - m_size.y;
		}
		else if (m_anchor == RectAnchor::BottomRight)
		{
			result.left		= position.x - m_size.x;
			result.top		= position.y - m_size.y;
		}

		result.width = m_size.x;
		result.height = m_size.y;
		return result;
	}


	RectTransform& RectTransform::operator=(const RectTransform& rhs)
	{// Not entirely correct, we only copy  rectTransform stuff, Owner/parent/etc isn't moved
		this->m_position	= rhs.m_position;
		this->m_rotation	= rhs.m_rotation;
		this->m_size		= rhs.m_size;
		this->m_anchor		= rhs.m_anchor;
		return *this;
	}

	void RectTransform::Debug(view::IViewStrategy* viewStrategy)
	{
		auto bb				= GetBoundingBox();
		math::Vec2 center	= { bb.left + bb.width / 2, bb.top + bb.height / 2 };
		math::Vec2 size		= { bb.width, bb.height };

		viewStrategy->DebugRenderRectangle(GetPositionSpace(), center, size, GetRotation(), sf::Color::Yellow, sf::Color::Transparent);
	}
}