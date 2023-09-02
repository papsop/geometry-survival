#include "RectTransform.h"

#include "../../Core/GameObject/GameObject.h"

namespace Engine {

RectTransform::RectTransform(GameObject& owner, const TransformDefinition& def)
    : ITransform(owner, def), m_position(def.Position), m_rotation(def.Rotation), m_size(def.Size), m_anchor(def.Anchor)
{
}

void RectTransform::SetPosition(math::Vec2 pos)
{
  m_position = pos;
  OnTransformChanged.Invoke();
}

math::Vec2 RectTransform::GetPosition() const
{
  // Calculate relative position
  math::Vec2 parentPos = {0.0f, 0.0f};
  math::Vec2 parentSize = {0.0f, 0.0f};
  math::Vec2 myPos;

  // Get parent position
  if (m_parent) {
    auto parentRect = dynamic_cast<RectTransform*>(m_parent->GetTransform());
    if (parentRect) {
      auto parentBB = parentRect->GetBoundingBox();
      parentPos = {parentBB.left, parentBB.top};
      parentSize = {parentBB.width, parentBB.height};
    }
  }

  // Check my constraints
  // each constraint calculates my relative position to parent
  // if given constraint isn't set, use m_position property
  if (m_constraints[static_cast<size_t>(ConstraintParam::X)])
    myPos.x = m_constraints[static_cast<size_t>(ConstraintParam::X)]->CalculateValue(parentSize.x) + parentPos.x;
  else
    myPos.x = m_position.x + parentPos.x;

  if (m_constraints[static_cast<size_t>(ConstraintParam::Y)])
    myPos.y = m_constraints[static_cast<size_t>(ConstraintParam::Y)]->CalculateValue(parentSize.y) + parentPos.y;
  else
    myPos.y = m_position.y + parentPos.y;

  return myPos;
}

float RectTransform::GetRotation() const { return 0.0f; }

void RectTransform::SetRotationDeg(float rotation)
{
  m_rotation = math::DEG_TO_RAD(rotation);
  OnTransformChanged.Invoke();
}

void RectTransform::SetRotationRad(float rotation)
{
  m_rotation = rotation;
  OnTransformChanged.Invoke();
}

math::Vec2 RectTransform::Forward() const
{  // doesn't make sense in rectTransform
  return {0.0f, 0.0f};
}

ITransform::AbsoluteTransform RectTransform::GetAbsoluteTransform() const
{
  ITransform::AbsoluteTransform result;
  auto bb = GetBoundingBox();
  result.Position = {bb.left, bb.top};
  result.Rotation = GetRotation();
  result.Scale = {1.0f, 1.0f};
  result.Space = GetPositionSpace();
  return result;
}

void RectTransform::SetSize(math::Vec2 size)
{
  m_size = size;
  OnTransformChanged.Invoke();
}

math::Vec2 RectTransform::GetSize() const
{
  // Calculate relative position
  math::Vec2 mySize;
  math::Vec2 parentSize = {0.0f, 0.0f};

  // Get parent size
  if (m_parent) {
    auto parentRect = dynamic_cast<RectTransform*>(m_parent->GetTransform());
    if (parentRect) {
      auto parentBB = parentRect->GetBoundingBox();
      parentSize = {parentBB.width, parentBB.height};
    }
  }

  // Check constraints
  if (m_constraints[static_cast<size_t>(ConstraintParam::Width)] != nullptr)
    mySize.x = m_constraints[static_cast<size_t>(ConstraintParam::Width)]->CalculateValue(parentSize.x);
  else
    mySize.x = m_size.x;

  if (m_constraints[static_cast<size_t>(ConstraintParam::Height)])
    mySize.y = m_constraints[static_cast<size_t>(ConstraintParam::Height)]->CalculateValue(parentSize.y);
  else
    mySize.y = m_size.y;

  return mySize;
}

sf::FloatRect RectTransform::GetBoundingBox() const
{
  sf::FloatRect result;
  math::Vec2 position = GetPosition();
  math::Vec2 size = GetSize();

  if (m_anchor == RectAnchor::TopLeft) {
    result.left = position.x;
    result.top = position.y;
  }
  else if (m_anchor == RectAnchor::TopCenter) {
    result.left = position.x - (size.x / 2);
    result.top = position.y;
  }
  else if (m_anchor == RectAnchor::TopRight) {
    result.left = position.x - size.x;
    result.top = position.y;
  }
  else if (m_anchor == RectAnchor::CenterLeft) {
    result.left = position.x;
    result.top = position.y - (size.y / 2);
  }
  else if (m_anchor == RectAnchor::CenterCenter) {
    result.left = position.x - (size.x / 2);
    result.top = position.y - (size.y / 2);
  }
  else if (m_anchor == RectAnchor::CenterRight) {
    result.left = position.x - size.x;
    result.top = position.y - (size.y / 2);
  }
  else if (m_anchor == RectAnchor::BottomLeft) {
    result.left = position.x;
    result.top = position.y - size.y;
  }
  else if (m_anchor == RectAnchor::BottomCenter) {
    result.left = position.x - (size.x / 2);
    result.top = position.y - size.y;
  }
  else if (m_anchor == RectAnchor::BottomRight) {
    result.left = position.x - size.x;
    result.top = position.y - size.y;
  }

  result.width = size.x;
  result.height = size.y;
  return result;
}

RectTransform& RectTransform::operator=(const RectTransform& rhs)
{  // Not entirely correct, we only copy  rectTransform stuff, Owner/parent/etc isn't moved
  this->m_position = rhs.m_position;
  this->m_rotation = rhs.m_rotation;
  this->m_size = rhs.m_size;
  this->m_anchor = rhs.m_anchor;
  return *this;
}

void RectTransform::Debug(view::IViewStrategy* viewStrategy)
{
  if (!m_owner.IsActive()) return;

  auto bb = GetBoundingBox();
  math::Vec2 center = {bb.left + bb.width / 2, bb.top + bb.height / 2};
  math::Vec2 size = {bb.width, bb.height};

  viewStrategy->DebugRenderRectangle(GetPositionSpace(), center, size, GetRotation(), sf::Color::Yellow, sf::Color::Transparent);
}

void RectTransform::SetScale(math::Vec2 scale) { return; }

}  // namespace Engine
