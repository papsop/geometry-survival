#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Core/StateMachine/PushdownStateMachine.h>
#include <Engine/Managers/PhysicsManager.h>
#include <Engine/Managers/EventManager.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"
#include "EnemyComponent.h"

namespace Game
{
	class AIChasePlayerComponent : public Engine::IComponent,
		public Engine::IEventListener<event::E_PlayerTookDamage>,
		public Engine::IEventListener<event::E_GameStateChanged>
	{
	public:
		AIChasePlayerComponent(Engine::GameObject& obj);
		~AIChasePlayerComponent() override;

		void VirtualOnCreate() override;
		void OnDestroy() override;

		void Update(float dt) override;

	protected:
    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

		void ReceiveEvent(const event::E_PlayerTookDamage& eventData) override;
		void ReceiveEvent(const event::E_GameStateChanged& eventData) override;

	private:
		void ApplyKnockbackFromPlayer();

		Engine::GameObject* m_target;

		EnemyComponent* m_enemyComponent;
	};
}