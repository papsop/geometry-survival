#include "AIChaseTargetComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Core/GameObject/GameObjectTag.h>
#include <Engine/Core/Scene/Scene.h>

#include "../Actor/ActorComponent.h"
#include "../States/Actor_ChaseTarget.h"
#include "../States/Actor_Stunned.h"
#include "../../Core/GameObject/GameObjectFactory.h"

namespace Game
{

	AIChaseTargetComponent::AIChaseTargetComponent(Engine::GameObject& obj, Engine::GameObject* target)
		: IComponent(obj)
		, m_target(target)
	{
		SetRequiredComponents<ActorComponent>();
	}

	void AIChaseTargetComponent::OnCreate()
	{
		auto actorComponent = Owner.GetComponent<ActorComponent>();

		m_stateMachine.AddState<Actor_ChaseTarget>(actorComponent, m_target);
		m_stateMachine.AddState<Actor_Stunned>(actorComponent, 0.25f);

		m_stateMachine.TransitionTo<Actor_ChaseTarget>();

		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	AIChaseTargetComponent::~AIChaseTargetComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void AIChaseTargetComponent::Update(float dt)
	{
		m_stateMachine.Update(dt);
	}

	void AIChaseTargetComponent::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MessageType::MSG_DIED)
		{
			ExperienceGlobeDef experienceGlobeDef;
			experienceGlobeDef.Position = Owner.GetTransform().Position;

			Owner.GetScene().AddGameObject(GameObjectFactory::CreateExperienceGlobe(experienceGlobeDef)->ID);
		}
	}

	void AIChaseTargetComponent::OnCollisionStart(Engine::GameObject* other)
	{
		// check if player bullet
		if (other->Tag != Engine::GameObjectTag::PLAYER_BULLET)
			return;

		// transition to stun
		m_stateMachine.TransitionTo<Actor_Stunned>();

		// apply knockback
		auto actorComponent = Owner.GetComponent<ActorComponent>();
		Engine::math::Vec2 knockBackDirection = Owner.GetTransform().Position - other->GetTransform().Position;
		actorComponent->AddCommand<KnockBackCommand>(knockBackDirection.x, knockBackDirection.y);
	}

}


