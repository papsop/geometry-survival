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
    {
        SetRequiredComponents<Engine::PhysicsBodyComponent>();

        m_RPGActor = std::unique_ptr<RPGActor>(new RPGActor());
        m_RPGActor->SetStatBase(RPGStats::MAX_HEALTH, 10.0f);
        m_RPGActor->SetStatBase(RPGStats::CURRENT_HEALTH, 10.0f);
        m_RPGActor->SetStatBase(RPGStats::MOVEMENT_SPEED, movementSpeed);
    }

    void ActorComponent::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    ActorComponent::~ActorComponent()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }

    void ActorComponent::Move(Engine::math::Vec2 dir)
    {
        auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
        auto mass = physBody->GetMass();

        auto actualVelocity = physBody->GetLinearVelocity();
        dir *= m_RPGActor->GetStat(RPGStats::MOVEMENT_SPEED);
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

	void ActorComponent::ApplyDamage(float amount)
	{
        auto currentHP = m_RPGActor->GetStat(RPGStats::CURRENT_HEALTH);
        m_RPGActor->SetStatBase(RPGStats::CURRENT_HEALTH, currentHP - amount);
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

	void ActorComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
        // name
        Engine::math::Vec2 pos = Owner.GetTransform().Position + Engine::math::Vec2(0.0f, 3.0f);
        viewStrategy->DebugRenderText(Owner.DebugName, pos, 12.0f, sf::Color::Yellow);

        // currentHealth/maxHealth
		pos = Owner.GetTransform().Position + Engine::math::Vec2(0.0f, 4.0f);
        std::string healthString = std::to_string( static_cast<int>(m_RPGActor->GetStat(RPGStats::CURRENT_HEALTH)) ) + \
                                    "/" + \
                                   std::to_string( static_cast<int>(m_RPGActor->GetStat(RPGStats::MAX_HEALTH)) );

		viewStrategy->DebugRenderText(healthString, pos, 12.0f, sf::Color::Yellow);
	}

	void ActorComponent::Update(float dt)
    {
        if(m_RPGActor != nullptr)
            m_RPGActor->Update(dt);

        while (!m_commandsQueue.empty())
        {
            m_commandsQueue.front()->Execute(*this);
            m_commandsQueue.pop();
        }

        if (m_RPGActor->GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
            Owner.Destroy();
    }
};