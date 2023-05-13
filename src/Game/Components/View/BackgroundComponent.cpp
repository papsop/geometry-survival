#include "BackgroundComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include "CameraComponent.h"

namespace Game
{

  BackgroundComponent::BackgroundComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
    SetRequiredComponents<Engine::SpriteDrawableComponent, CameraComponent>();
  }

  void BackgroundComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
    m_spriteComponent = Owner.GetComponent<Engine::SpriteDrawableComponent>();
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
		auto cameraTransformPos = Owner.GetTransform()->GetPosition();
		sf::Vector2f cameraPos = { cameraTransformPos.x, cameraTransformPos.y };
		m_spriteComponent->SetShaderParameter("cameraPos", cameraPos);
    m_spriteComponent->SetShaderParameter("textureSize", sf::Vector2f{3.2f, 3.2f});
  }

}