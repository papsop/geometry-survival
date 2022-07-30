#include "CameraComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj)
		: IComponent(obj)
	{
		m_cameraData.Center = Owner.GetTransform().Position;
		m_cameraData.Size = {128.2f, 72.f};
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