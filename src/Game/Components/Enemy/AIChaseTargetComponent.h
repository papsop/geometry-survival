#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/StateMachine/IState.h>

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

	private:
		Engine::GameObject* m_target;
		std::unique_ptr<Engine::IState> m_currentState;
	};
}