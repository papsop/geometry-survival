#include "EnemySpawnerComponent.h"
#include "../../Managers/GameManager.h"
#include "../../Managers/EnemySpawningManager.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include <Engine/Application.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

	EnemySpawnerComponent::EnemySpawnerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		m_currentCooldown = Engine::Application::Instance().GetGameManager<GameManager>()->GetSpawnCooldown();
	}

	void EnemySpawnerComponent::OnDestroy()
	{
		Engine::Application::Instance().GetGameManager<EnemySpawningManager>()->UnregisterSpawnerObject();
	}

	void EnemySpawnerComponent::VirtualOnActivated()
	{
		Engine::Application::Instance().GetGameManager<EnemySpawningManager>()->RegisterSpawnerObject(&Owner);
	}

	void EnemySpawnerComponent::VirtualOnDeactivated()
	{
		Engine::Application::Instance().GetGameManager<EnemySpawningManager>()->UnregisterSpawnerObject();
	}

}
