#include "BackgroundComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/RenderManager.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include "CameraComponent.h"

namespace Game
{

  BackgroundComponent::BackgroundComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
    SetRequiredComponents<Engine::SpriteDrawableComponent, CameraComponent>();
  }

  void BackgroundComponent::VirtualOnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
    m_spriteComponent = Owner.GetComponent<Engine::SpriteDrawableComponent>();
    
		auto resolution = Engine::RenderManager::Get().GetSettings().ResolutionEntry.Value;
		auto worldSize = Engine::RenderManager::Get().pixelsToCoords({ resolution.x, resolution.y });
		m_spriteComponent->SetSize(worldSize);
  }

	void BackgroundComponent::OnDestroy()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

  BackgroundComponent::~BackgroundComponent()
  {
  }

  void BackgroundComponent::VirtualOnActivated()
  {

  }

  void BackgroundComponent::VirtualOnDeactivated()
  {

  }

  void BackgroundComponent::FixedUpdate(float dt)
	{
		auto cameraTransformPos = Engine::RenderManager::Get().coordsPosToPixelsPos(Owner.GetTransform()->GetPosition());
		m_spriteComponent->SetShaderParameter("cameraPos", cameraTransformPos);
		//m_spriteComponent->SetShaderParameter("pixelsPerMeter", Engine::RenderManager::Get().GetPPM());
		m_spriteComponent->SetShaderParameter("textureSize", static_cast<sf::Vector2f>(m_spriteComponent->GetTextureSize()));
  }
}