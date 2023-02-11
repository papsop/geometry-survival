#include "AIChasePlayerComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Core/GameObject/GameObjectTag.h>
#include <Engine/Core/Scene/Scene.h>

#include "../../Managers/GameManager.h"
#include "../../Physics/Filters.h"
#include "../Actor/ActorComponent.h"
#include "../States/Actor.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{

	AIChasePlayerComponent::AIChasePlayerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<ActorComponent, EnemyComponent>();
	}

	void AIChasePlayerComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);

		auto actorComponent = Owner.GetComponent<ActorComponent>();
		m_stateMachine.AddState<Actor_ChasePlayer>(actorComponent);
	}


  void AIChasePlayerComponent::OnDestroy()
  {
    VirtualOnDeactivated();
  }

  AIChasePlayerComponent::~AIChasePlayerComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void AIChasePlayerComponent::VirtualOnActivated()
  {
    Engine::IEventListener<event::E_PlayerTookDamage>::RegisterListener();
  }

  void AIChasePlayerComponent::VirtualOnDeactivated()
  {
    Engine::IEventListener<event::E_PlayerTookDamage>::UnregisterListener();
  }

  void AIChasePlayerComponent::Update(float dt)
	{
		m_stateMachine.Update(dt);
	}

  void AIChasePlayerComponent::ProcessMessage(const Engine::Message& message)
  {
    if (message.Type == Engine::MessageType::Actor_TookDamage)
    {
      ApplyKnockbackFromPlayer();
    }
  }

  void AIChasePlayerComponent::ReceiveEvent(const event::E_PlayerTookDamage& eventData)
  {
    ApplyKnockbackFromPlayer();
  }

  void AIChasePlayerComponent::ApplyKnockbackFromPlayer()
  {
    // apply knockback from player
    auto* playerGO = Engine::Application::Instance().GetGameManager<GameManager>()->GetPlayerGameObject();
    auto* actorComponent = Owner.GetComponent<ActorComponent>();
    Engine::math::Vec2 knockBackDirection = Engine::math::V2fNormalize(Owner.GetTransform()->GetPosition() - playerGO->GetTransform()->GetPosition());
    actorComponent->AddCommand<KnockBackCommand>(knockBackDirection.x, knockBackDirection.y);

    // go to stun
    m_stateMachine.AddState<Actor_Stunned>(actorComponent, 1.0f);
  }

}
