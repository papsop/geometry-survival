#include "CameraComponent.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

	CameraComponent::CameraComponent(Engine::GameObject& obj, Engine::GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		m_cameraData.Center = Owner.GetTransform()->GetPosition();
	}

	void CameraComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	CameraComponent::~CameraComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void CameraComponent::Update(float dt)
	{
    if (m_target)
    {
			Owner.GetTransform()->SetPosition(m_target->GetTransform()->GetPosition());
		}

		m_cameraData.Center = Owner.GetTransform()->GetPosition();
		Engine::ViewManager::Get().GetViewStrategy()->SetView(m_cameraData);
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

};