#include "CameraComponent.h"
#include "../../Managers/SubsystemManager.h"

namespace Engine
{

	CameraComponent::CameraComponent(GameObject& obj)
		: IComponent(obj)
		, m_view({0.0f, 0.0f}, sf::Vector2f(800.0f, 600.0f))
	{
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
		m_view.setCenter({ 0.0f, 0.0f });
		SubsystemManager::Get().GetViewSubsystem().GetViewStrategy()->SetView(m_view);
	
	}

	void CameraComponent::OnCollision(GameObject& other)
	{
		
	}

};