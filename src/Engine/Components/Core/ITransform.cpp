#include "ITransform.h"

#include <algorithm>

#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/GameObjectManager.h"

namespace Engine {

ITransform::ITransform(GameObject& owner, const TransformDefinition& def)
    : m_owner(owner), m_transformType(def.TransType), m_positionType(def.PosType), m_space(def.Space)
{
  SetParent(def.Parent);
}

void ITransform::OnDestroy()
{
  LOG_INFO("Destroying transform from %s", m_owner.DebugName);
  // Deleting only myself
  if (m_parent != nullptr) {
    m_parent->GetTransform()->RemoveChild(&m_owner);
  }

  // Delete all my children
  // First set their parent to nullptr - otherwise there will be a dangling ref
  for (auto& child : m_children) {
    child->GetTransform()->SetParent(nullptr);
    child->Destroy();
  }
}

void ITransform::SetParent(GameObject* parent) { m_parent = parent; }

void ITransform::AddChild(GameObject* child)
{  // just ignore the call if already a child
  if (std::find(m_children.begin(), m_children.end(), child) == m_children.end()) {
    m_children.emplace_back(child);
    child->GetTransform()->SetParent(&m_owner);
  }
}

void ITransform::RemoveChild(GameObject* child)
{
  if (std::find(m_children.begin(), m_children.end(), child) != m_children.end()) {
    m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](const GameObject* val) { return val == child; }), m_children.end());

    child->GetTransform()->SetParent(nullptr);
  }
}

void ITransform::SetPositionType(PositionType posType) { m_positionType = posType; }

}  // namespace Engine
