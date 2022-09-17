#include "ExperienceBarComponent.h"
#include <Engine/Application.h>
#include "../../Managers/GameManager.h"

namespace Game
{

	ExperienceBarComponent::ExperienceBarComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
	}

	void ExperienceBarComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);

		auto* gameManager = Engine::Application::Instance().GetGameManager<GameManager>();
		m_playerLevelComponent = gameManager->GetPlayerGameObject()->GetComponent<LevelComponent>();
		m_parentTransform = Owner.GetTransform()->GetParent()->GetTransformAs<Engine::RectTransform>();
		m_ownerTransform = Owner.GetTransformAs<Engine::RectTransform>();
	}

	ExperienceBarComponent::~ExperienceBarComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void ExperienceBarComponent::Update(float dt)
	{
		auto parentSize = m_parentTransform->GetSize();
		parentSize.x *= m_playerLevelComponent->GetCurrentLevelProgress();

		m_ownerTransform->SetSize(parentSize);
	}



}