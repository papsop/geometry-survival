#include "ActorComponent.h"
#include "WeaponComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{

    ActorComponent::ActorComponent(Engine::GameObject& obj, float movementSpeed)
        : IComponent(obj)
        , m_commandsQueue()
        , m_movementSpeed(movementSpeed)
    {
        SetRequiredComponents<Engine::PhysicsBodyComponent>();
    }

    void ActorComponent::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    ActorComponent::~ActorComponent()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }

    void ActorComponent::AddCommand(std::unique_ptr<ICommand> command)
    {
        m_commandsQueue.push(std::move(command)); 
    }
     
    void ActorComponent::Move(Engine::math::Vec2 dir)
    {
        auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
        auto mass = physBody->GetMass();

        auto actualVelocity = physBody->GetLinearVelocity();
        dir *= m_movementSpeed;
        auto desiredVelocity = dir;

        auto impulse = (desiredVelocity - actualVelocity);
        impulse *= mass;
        physBody->ApplyImpulseToCenter(impulse);
    }

    void ActorComponent::KnockBack(Engine::math::Vec2 dir)
	{
		auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
		auto mass = physBody->GetMass();

        auto actualVelocity = physBody->GetLinearVelocity();
        dir *= 2.0f;
        auto desiredVelocity = dir;

        auto impulse = (desiredVelocity - actualVelocity);
        impulse *= mass;
        physBody->ApplyImpulseToCenter(impulse);
    }

    void ActorComponent::Rotate(float angle)
    {
        auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
		physBody->GetB2Body()->SetTransform(Owner.GetTransform().Position, angle);
        physBody->GetB2Body()->SetAngularVelocity(0);
    }

    void ActorComponent::Fire()
    {
        auto weaponComp = Owner.GetComponent<WeaponComponent>();
        if (weaponComp) 
        {
            weaponComp->Fire();
        }
    }

	void ActorComponent::ProcessMessage(const Engine::Message& message)
	{
		if (message.Type == Engine::MessageType::MSG_Test)
		{
			//LOG_WARN("[%s] received MSG_TEST", Owner.DebugName);
		}
	}

	void ActorComponent::OnCollisionStart(Engine::GameObject* other)
	{
        Owner.SendMessageTo(other, Engine::MSG_Test);
	}

	void ActorComponent::Update(float dt)
    {
        while (!m_commandsQueue.empty())
        {
            m_commandsQueue.front()->Execute(*this);
            m_commandsQueue.pop();
        }
    }
};