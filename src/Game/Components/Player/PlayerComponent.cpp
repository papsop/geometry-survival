#include "PlayerComponent.h"
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
namespace Game
{

	PlayerComponent::PlayerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
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