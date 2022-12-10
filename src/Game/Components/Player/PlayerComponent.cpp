#include "PlayerComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/PhysicsManager.h>

#include "../../Managers/GameManager.h"
#include "../Actor/ActorComponent.h"
namespace Game
{

  PlayerComponent::PlayerComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
  }

  void PlayerComponent::OnCollisionStart(Engine::CollisionData& collision)
  {
    if (collision.Other->Tag != Engine::GameObjectTag::ENEMY)
      return;

    auto* playerActor = Owner.GetComponent<ActorComponent>();
    if (playerActor)
    {
      playerActor->ApplyDamage(1);
    }
  }

  void PlayerComponent::OnDestroy()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->UnregisterPlayerGameObject();
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