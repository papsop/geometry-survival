#include "PlayerComponent.h"
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
namespace Game
{

	PlayerComponent::PlayerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		Engine::Application::Instance().GetGameManager<GameManager>()->RegisterPlayerGameObject(&obj);
	}

}