#include "CameraComponent.h"
#include "../../Managers/ComponentManager.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj)
		: IComponent(obj)
	{
		m_cameraData.Center = Owner.GetTransform().Position;
		m_cameraData.Size = {80.f, 60.f};
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

	void CameraComponent::OnCollisionStart(GameObject* other)
	{
		
	}

};