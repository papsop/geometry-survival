#include "PhysicsBodyComponent.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/PhysicsManager.h"
#include "../../Utils/AllUtils.h"

namespace Engine {

PhysicsBodyComponent::PhysicsBodyComponent(GameObject& obj, PhysicsBodyDef& def)
    : IComponent(obj), m_categoryBits(def.CategoryBits), m_maskBits(def.MaskBits), m_isBullet(def.IsBullet), m_bodyType(def.BodyType)
{
  // TODO: how to deal with physics and absolute relative position/angle
  b2BodyDef bodyDef;
  bodyDef.type = m_bodyType;
  bodyDef.position = Owner.GetTransform()->GetAbsoluteTransform().Position;
  bodyDef.bullet = m_isBullet;
  bodyDef.angle = Owner.GetTransform()->GetAbsoluteTransform().Rotation;
  bodyDef.enabled = false;  // default always false, activate it in function VirtualOnActivated
  bodyDef.fixedRotation = true;
  bodyDef.userData.pointer = Owner.ID;
  m_b2Body = PhysicsManager::Get().CreateBody(&bodyDef);

  Owner.GetTransform()->OnTransformChanged.AddListener(this, &PhysicsBodyComponent::OnTransformChangedCallback);
}

void PhysicsBodyComponent::VirtualOnCreate() { PhysicsManager::Get().RegisterComponent(this); }

void PhysicsBodyComponent::VirtualOnActivated() { m_b2Body->SetEnabled(true); }

void PhysicsBodyComponent::VirtualOnDeactivated() { m_b2Body->SetEnabled(false); }

void PhysicsBodyComponent::ApplyImpulseToCenter(const math::Vec2& impulse) { m_b2Body->ApplyLinearImpulse(impulse, m_b2Body->GetWorldCenter(), true); }

void PhysicsBodyComponent::ApplyTorque(float torque) { m_b2Body->ApplyTorque(torque, true); }

void PhysicsBodyComponent::SetLinearVelocity(float velocity) { SetLinearVelocity(Owner.GetTransform()->Forward(), velocity); }

void PhysicsBodyComponent::SetLinearVelocity(math::Vec2 direction, float velocity)
{
  auto actualVelocity = GetLinearVelocity();
  auto desiredVelocity = direction;
  desiredVelocity *= velocity;

  auto impulse = (desiredVelocity - actualVelocity);
  if (impulse.Length() <= 0.005f) return;

  impulse *= GetMass();
  ApplyImpulseToCenter(impulse);
}

void PhysicsBodyComponent::Debug(VisualDebugContext& debugContext)
{
  std::string text = std::to_string(GetLinearVelocity().Length());
  Engine::math::Vec2 pos = Owner.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, -1.0f);
  debugContext.DebugRenderText(ITransform::PositionSpace::WorldSpace, text, pos, true, 12.0f, sf::Color::Red);
}

void PhysicsBodyComponent::OnTransformChangedCallback()
{
  auto& absoluteTransform = Owner.GetTransform()->GetAbsoluteTransform();
  m_b2Body->SetTransform(absoluteTransform.Position, absoluteTransform.Rotation);
}

PhysicsBodyComponent::~PhysicsBodyComponent()
{
  PhysicsManager::Get().UnregisterComponent(this);
  PhysicsManager::Get().DeleteBody(m_b2Body);
}

void PhysicsBodyComponent::FixedUpdate(float dt)
{
  Owner.GetTransform()->SetPosition(m_b2Body->GetPosition());
  Owner.GetTransform()->SetRotationRad(m_b2Body->GetAngle());
}
};  // namespace Engine
