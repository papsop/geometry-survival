#include "BackgroundComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>

namespace Game
{

  BackgroundComponent::BackgroundComponent(Engine::GameObject& obj, Engine::GameObject* target)
    : IComponent(obj)
    , m_target(target)
  {
    SetRequiredComponents<Engine::SpriteDrawableComponent>();
  }

  void BackgroundComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
  }

  BackgroundComponent::~BackgroundComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void BackgroundComponent::VirtualOnActivated()
  {

  }

  void BackgroundComponent::VirtualOnDeactivated()
  {

  }

  void BackgroundComponent::FixedUpdate(float dt)
  {
    auto cameraTransformPos = m_target->GetTransform()->GetPosition();
    sf::Vector2f cameraPos = {cameraTransformPos.x, cameraTransformPos.y};
    Owner.GetComponent<Engine::SpriteDrawableComponent>()->SetShaderParameter("cameraPos", cameraPos);
    Owner.GetTransform()->SetPosition(cameraTransformPos);
  }

}