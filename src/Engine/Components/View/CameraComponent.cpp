#include "CameraComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj, GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		m_cameraData.Center = Owner.GetTransform().Position;
	}

	void CameraComponent::OnCreate()
	{
		ViewManager::Get().RegisterComponent(this);
	}

	CameraComponent::~CameraComponent()
	{
		ViewManager::Get().UnregisterComponent(this);
	}

	void CameraComponent::Update(float dt)
	{
		if (m_target)
		{	// camera movement based on target
			// if no target present - just static position
			
			Owner.GetTransform().SetPosition(m_target->GetTransform().Position);
		}

		m_cameraData.Center = Owner.GetTransform().Position;
		ViewManager::Get().GetViewStrategy()->SetView(m_cameraData);
	}

	void CameraComponent::SetTarget(GameObject* newTarget)
	{
		m_target = newTarget;
	}

};