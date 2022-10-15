#include "PlayerSpawnerComponent.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{

  PlayerSpawnerComponent::PlayerSpawnerComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
  }

  void PlayerSpawnerComponent::CreatePlayerObject()
  {
    PlayerObjectDef def;
    def.IncludeInputControl = true;
    auto* player = GameObjectFactory::CreatePlayerObject(def);

    Owner.GetTransform()->AddChild(player);
  }

}