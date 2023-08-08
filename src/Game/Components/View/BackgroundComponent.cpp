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
    Engine::RenderManager::Get().OnSettingsChanged.AddListener(this, &BackgroundComponent::RenderManagerSettingsChanged);
    RenderManagerSettingsChanged(); // set first size
  }

	void BackgroundComponent::OnDestroy()
	{
    Engine::RenderManager::Get().OnSettingsChanged.RemoveListener(this);
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
		auto cameraTransformPos = Engine::RenderManager::Get().coordsPosToPixelsPos(Owner.GetTransform()->GetPosition());
		m_spriteComponent->SetShaderParameter("cameraPos", cameraTransformPos);
		//m_spriteComponent->SetShaderParameter("pixelsPerMeter", Engine::RenderManager::Get().GetPPM());
		m_spriteComponent->SetShaderParameter("textureSize", static_cast<sf::Vector2f>(m_spriteComponent->GetTextureSize()));
  }

	void BackgroundComponent::RenderManagerSettingsChanged()
	{
    auto settings = Engine::RenderManager::Get().GetSettings();
    auto resolution = settings.ResolutionEntry.Value;
    auto worldSize = Engine::RenderManager::Get().pixelsToCoords({ resolution.x, resolution.y });
    m_spriteComponent->SetSize(worldSize);
	}

}