#include "AIChaseTargetComponent.h"
#include <Engine/Managers/ComponentManager.h>

#include "../Actor/ActorComponent.h"
#include "../States/Actor_ChaseTarget.h"
#include "../States/Actor_KnockedBack.h"

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
		m_stateContainer.CreateAndSetState<Actor_ChaseTarget>(actorComponent, m_target);

		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	AIChaseTargetComponent::~AIChaseTargetComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void AIChaseTargetComponent::Update(float dt)
	{
		m_stateContainer.Update(dt);
	}

	void AIChaseTargetComponent::ProcessMessage(const Engine::Message& message)
	{
		
	}

	void AIChaseTargetComponent::OnCollisionStart(Engine::GameObject* other)
	{
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		m_stateContainer.CreateAndSetState<Actor_KnockedBack>(actorComponent, other->GetTransform());
	}

}


