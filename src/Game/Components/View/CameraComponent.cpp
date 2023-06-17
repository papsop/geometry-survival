#include "CameraComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/RenderManager.h>

namespace Game
{

	CameraComponent::CameraComponent(Engine::GameObject& obj, Engine::GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		m_cameraData.Center = Owner.GetTransform()->GetPosition();
	}

	void CameraComponent::VirtualOnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

  void CameraComponent::VirtualOnActivated()
  {
    IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
		IEventListener<event::E_GameStateChanged>::RegisterListener();
  }

  void CameraComponent::VirtualOnDeactivated()
  {
    IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
  }

	CameraComponent::~CameraComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void CameraComponent::FixedUpdate(float dt)
	{
    if (m_target)
    {
			Owner.GetTransform()->SetPosition(m_target->GetTransform()->GetPosition());
		}

		m_cameraData.Center = Owner.GetTransform()->GetPosition();
		//Engine::ViewManager::Get().GetViewStrategy()->SetView(m_cameraData);
		Engine::RenderManager::Get().SetView(m_cameraData);
	}

	void CameraComponent::SetTarget(Engine::GameObject* newTarget)
	{
		m_target = newTarget;
	}

	void CameraComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
	}

  void CameraComponent::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData)
  {
		m_target = eventData.PlayerObject;
  }

	void CameraComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		//SetEnabled(eventData.NewState == GameState::Gameplay);
	}

};