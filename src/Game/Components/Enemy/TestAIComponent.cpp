#include "TestAIComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Utils/VectorUtils.h>

#include "../States/Actor_ChasePlayer.h"
#include "../Actor/ActorComponent.h"

namespace Game
{

	TestAIComponent::TestAIComponent(Engine::GameObject& obj, Engine::GameObject* player)
		: IComponent(obj)
	{
		//m_currentState = std::make_unique<Actor_ChasePlayer>();
		SetRequiredComponents<ActorComponent>();
		Engine::ComponentManager::Get().RegisterComponent(this);
		m_player = player;
	}

	TestAIComponent::~TestAIComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void TestAIComponent::Update(float dt)
	{
		if (m_currentState)
			m_currentState->Update(dt);

		// chase
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		Engine::math::Vec2 meToPlayer = Engine::math::V2fNormalize(m_player->GetTransform().Position - Owner.GetTransform().Position);
		actorComponent->AddCommand(std::make_unique<MoveCommand>(meToPlayer.x * 0.5f, meToPlayer.y * 0.5f));

		// rotate
		float angle = Engine::math::AngleBetweenVecs(Owner.GetTransform().Position, m_player->GetTransform().Position);
		actorComponent->AddCommand(std::make_unique<RotateCommand>(angle));
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
