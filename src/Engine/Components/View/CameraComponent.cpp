#include "CameraComponent.h"
#include "../../Managers/ComponentManager.h"
#include "../Physics.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj, GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		m_cameraData.Center = Owner.GetTransform()->GetPosition();
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
		{	// camera based on target
			Owner.GetTransform()->SetPosition(m_target->GetTransform()->GetPosition());
		} // if no target present - just static position

		m_cameraData.Center = Owner.GetTransform()->GetPosition();
		ViewManager::Get().GetViewStrategy()->SetView(m_cameraData);
	}

	void CameraComponent::SetTarget(GameObject* newTarget)
	{
		m_target = newTarget;
	}

	void CameraComponent::Debug(view::IViewStrategy* viewStrategy)
	{
	}

};