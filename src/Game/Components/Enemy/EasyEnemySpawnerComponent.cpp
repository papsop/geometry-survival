#include "EasyEnemySpawnerComponent.h"
#include "../../Managers/GameManager.h"
#include "../../Core/GameObject/GameObjectFactory.h"

#include <Engine/Application.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

	EasyEnemySpawnerComponent::EasyEnemySpawnerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{
		m_currentCooldown = Engine::Application::Instance().GetGameManager<GameManager>()->GetSpawnCooldown();
	}

	void EasyEnemySpawnerComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	EasyEnemySpawnerComponent::~EasyEnemySpawnerComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void EasyEnemySpawnerComponent::Update(float dt)
	{
		m_currentCooldown -= dt;
		if (m_currentCooldown <= 0.0f)
		{
			auto* gameManager = Engine::Application::Instance().GetGameManager<GameManager>();
			auto* player = gameManager->GetPlayerGameObject();

			if (player)
			{
        // spawn
        EnemyFactoryDef enemyFactoryDef;
        enemyFactoryDef.MovementSpeed = 5.0f;
        enemyFactoryDef.Player = player;
        enemyFactoryDef.Position = gameManager->GetRandomEnemySpawnPoint();
        auto enemyObj = GameObjectFactory::CreateEnemy(enemyFactoryDef);
        Owner.GetTransform()->AddChild(enemyObj);
        //Owner.GetScene().AddGameObject(enemyObj->ID);

        m_currentCooldown = Engine::Application::Instance().GetGameManager<GameManager>()->GetSpawnCooldown();
			}
		}
	}


}
