#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/StateMachine/IState.h>

namespace Game
{
	class TestAIComponent : public Engine::IComponent
	{

	public:
		TestAIComponent(Engine::GameObject& obj, Engine::GameObject* player);
		~TestAIComponent() override;

		void OnCreate() override {};

		void Update(float dt) override;

		void OnCollisionStart(Engine::GameObject* other) override;
		void OnCollisionEnd(Engine::GameObject* other) override;

		void ProcessMessage(const Engine::Message& message) override;
	private:
		std::unique_ptr<Engine::IState> m_currentState = nullptr;
		Engine::GameObject* m_player;
	};
}