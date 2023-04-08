#include "PlayerComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Managers/EventManager.h>

#include "../../Core/EventData.h"
#include "../../Managers/GameManager.h"
#include "../Actor/RPGComponent.h"
namespace Game
{

  PlayerComponent::PlayerComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
    SetRequiredComponents<ActorComponent, RPGComponent>();

    m_actorComponent = Owner.GetComponent<ActorComponent>();
    m_rpgComponent = Owner.GetComponent<RPGComponent>();
  }

	void PlayerComponent::OnCreate()
	{
    m_actorComponent->OnZeroHealth.AddListener(this, &PlayerComponent::OnDeath);
	}

	void PlayerComponent::OnDestroy()
	{
    m_actorComponent->OnZeroHealth.RemoveListener(this);
	}

	void PlayerComponent::VirtualOnActivated()
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->RegisterPlayerGameObject(&Owner);
	}

	void PlayerComponent::VirtualOnDeactivated()
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->UnregisterPlayerGameObject();
	}

  void PlayerComponent::OnCollisionStart(Engine::CollisionData& collision)
  {

  }

  void PlayerComponent::ProcessMessage(const Engine::Message& message)
  {
    if (message.Type == Engine::MessageType::Actor_TookDamage_Knockback ||
        message.Type == Engine::MessageType::Actor_TookDamage_NoKnockback)
    {
      Engine::EventManager::Get().DispatchEvent(event::E_PlayerTookDamage());
    }
  }

	void PlayerComponent::OnDeath()
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->UnregisterPlayerGameObject();
    Engine::EventManager::Get().DispatchEvent(event::E_PlayerDied());
    Owner.Destroy();
	}

}