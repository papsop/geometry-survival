#include "TestAIComponent.h"
#include "../States/Actor_ChasePlayer.h"

namespace Game
{

	TestAIComponent::TestAIComponent(Engine::GameObject& obj, Engine::GameObject* player)
		: IComponent(obj)
	{
		m_currentState = std::make_unique<Actor_ChasePlayer>();
	}

	void TestAIComponent::Update(float dt)
	{
		if (m_currentState)
			m_currentState->Update(dt);
	}

	void TestAIComponent::OnCollisionStart(Engine::GameObject* other)
	{
		
	}

	void TestAIComponent::OnCollisionEnd(Engine::GameObject* other)
	{
		
	}

	void TestAIComponent::ProcessMessage(const Engine::Message& message)
	{
		if (m_currentState)
			m_currentState->ProcessMessage(message);
	}

}
