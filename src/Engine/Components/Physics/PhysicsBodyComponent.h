#pragma once
#include <box2d/b2_body.h>

#include "../../Debug/IDebuggable.h"
#include "../Core.h"

namespace Engine {

struct PhysicsBodyDef {
  b2BodyType BodyType = b2_staticBody;
  bool IsBullet = false;
  uint16 CategoryBits = 0x0000;  // I'm xxx
  uint16 MaskBits = 0x0000;      // I collide with yyy
};

class PhysicsBodyComponent : public IComponent, public IDebuggableComponent {
 public:
  PhysicsBodyComponent(GameObject& obj, PhysicsBodyDef& def);
  ~PhysicsBodyComponent() override;

  void FixedUpdate(float dt) override;
  void VirtualOnCreate() override;

  b2Body* GetB2Body() { return m_b2Body; }

  void ApplyImpulseToCenter(const math::Vec2& impulse);
  void ApplyTorque(float torque);
  b2Vec2 GetLinearVelocity() { return m_b2Body->GetLinearVelocity(); }
  void SetLinearVelocity(float velocity);
  void SetLinearVelocity(math::Vec2 direction, float velocity);
  float GetMass() { return m_b2Body->GetMass(); }

  uint16 GetCategoryBits() { return m_categoryBits; }
  uint16 GetMaskBits() { return m_maskBits; }

  void Debug(VisualDebugContext& debugContext) override;

  void OnTransformChangedCallback();

 private:
  b2Body* m_b2Body = nullptr;
  b2BodyType m_bodyType;
  bool m_isBullet;
  uint16 m_categoryBits;
  uint16 m_maskBits;

 protected:
  void VirtualOnActivated() override;
  void VirtualOnDeactivated() override;

  friend class SceneSerializer;
};
}  // namespace Engine
