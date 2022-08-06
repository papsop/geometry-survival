#include "CameraComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj)
		: IComponent(obj)
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
		m_cameraData.Center = Owner.GetTransform().Position;
		ViewManager::Get().GetViewStrategy()->SetView(m_cameraData);	
	}

};