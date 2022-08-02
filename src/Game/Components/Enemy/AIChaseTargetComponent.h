#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Core/StateMachine/FiniteStateMachine.h>
#include <Engine/Managers/PhysicsManager.h>

namespace Game
{
	class AIChaseTargetComponent : public Engine::IComponent
	{
	public:
		AIChaseTargetComponent(Engine::GameObject& obj, Engine::GameObject* target);
		~AIChaseTargetComponent() override;

		void OnCreate() override;
		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;
		void OnCollisionStart(Engine::CollisionData& collision) override;

	private:
		Engine::GameObject* m_target;
	};
}