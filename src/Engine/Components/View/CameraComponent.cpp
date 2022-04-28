#include "CameraComponent.h"
#include "../../Managers/SubsystemManager.h"

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
		SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
	}

	CameraComponent::~CameraComponent()
	{
		SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
	}

	void CameraComponent::Update(float dt)
	{
		m_cameraData.Center = Owner.GetTransform().Position;
		SubsystemManager::Get().GetViewSubsystem().GetViewStrategy()->SetView(m_cameraData);	
	}

	void CameraComponent::OnCollisionStart(GameObject& other)
	{
		
	}

};