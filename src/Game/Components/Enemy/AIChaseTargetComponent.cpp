#include "AIChaseTargetComponent.h"
#include <Engine/Managers/ComponentManager.h>

#include "../Actor/ActorComponent.h"
#include "../States/Actor_ChaseTarget.h"

namespace Game
{

	AIChaseTargetComponent::AIChaseTargetComponent(Engine::GameObject& obj, Engine::GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		SetRequiredComponents<ActorComponent>();
	}

	void AIChaseTargetComponent::OnCreate()
	{
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		m_currentState = std::make_unique<Actor_ChaseTarget>(actorComponent, m_target);

		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	AIChaseTargetComponent::~AIChaseTargetComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void AIChaseTargetComponent::Update(float dt)
	{
		if (m_currentState != nullptr)
			m_currentState->Update(dt);
	}

	void AIChaseTargetComponent::ProcessMessage(const Engine::Message& message)
	{
		
	}
}


