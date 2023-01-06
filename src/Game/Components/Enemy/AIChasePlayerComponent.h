#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Managers/EventManager.h>

#include "../../Core/EventData.h"
#include "EnemyComponent.h"

namespace Game
{
	class AIChasePlayerComponent : public Engine::IComponent
	{
	public:
		AIChasePlayerComponent(Engine::GameObject& obj);
		~AIChasePlayerComponent() override;

		void OnCreate() override;
		void Update(float dt) override;
		void OnCollisionStart(Engine::CollisionData& collision) override;

	private:
		Engine::GameObject* m_target;
		Engine::PushdownStateMachine m_stateMachine;

		EnemyComponent* m_enemyComponent;
	};
}