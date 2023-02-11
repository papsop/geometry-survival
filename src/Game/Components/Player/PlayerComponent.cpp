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

  void PlayerComponent::OnCollisionStart(Engine::CollisionData& collision)
  {
    if (collision.Other->Tag != Engine::GameObjectTag::ENEMY)
      return;

    m_actorComponent->ApplyDamage(1, Actor_DamageSource::Collision);
  }

  void PlayerComponent::ProcessMessage(const Engine::Message& message)
  {
    if (message.Type == Engine::MessageType::Actor_TookDamage_Knockback ||
        message.Type == Engine::MessageType::Actor_TookDamage_NoKnockback)
    {
      Engine::EventManager::Get().DispatchEvent(event::E_PlayerTookDamage());
    }
  }

  void PlayerComponent::OnDestroy()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->UnregisterPlayerGameObject();

    
    // Player died because of HP
    if (m_rpgComponent->GetStat(RPGStats::CURRENT_HEALTH) <= 0)
    {
      Engine::EventManager::Get().DispatchEvent(event::E_PlayerDied());
    }
  }

  void PlayerComponent::VirtualOnActivated()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RegisterPlayerGameObject(&Owner);
  }

  void PlayerComponent::VirtualOnDeactivated()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->UnregisterPlayerGameObject();
  }

}