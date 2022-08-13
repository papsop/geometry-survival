#include "ActorComponent.h"
#include "WeaponComponent.h"
#include "RPGComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
    ActorComponent::ActorComponent(Engine::GameObject& obj)
        : IComponent(obj)
        , m_commandsQueue()
    {
        SetRequiredComponents<Engine::PhysicsBodyComponent, RPGComponent>();

        m_RPGComponent = Owner.GetComponent<RPGComponent>();
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
        dir *= m_RPGComponent->GetStat(RPGStats::MOVEMENT_SPEED);
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
        auto currentHP = m_RPGComponent->GetStat(RPGStats::CURRENT_HEALTH);
        m_RPGComponent->SetStatBase(RPGStats::CURRENT_HEALTH, currentHP - amount);
	}

	void ActorComponent::WeaponFire()
    {
        Owner.SendMessageTo(&Owner, Engine::MSG_Weapon_Fire);
    }

	void ActorComponent::WeaponReload()
	{
        Owner.SendMessageTo(&Owner, Engine::MSG_Weapon_Reload);
	}

	void ActorComponent::ProcessMessage(const Engine::Message& message)
	{
	}

	void ActorComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
        // name
        Engine::math::Vec2 pos = Owner.GetTransform().Position + Engine::math::Vec2(0.0f, 3.0f);
        viewStrategy->DebugRenderText(Owner.DebugName, pos, 12.0f, sf::Color::Yellow);

        // currentHealth/maxHealth
		pos = Owner.GetTransform().Position + Engine::math::Vec2(0.0f, 4.0f);
        std::string healthString = "HP " + std::to_string(static_cast<int>(m_RPGComponent->GetStat(RPGStats::CURRENT_HEALTH))) + \
                                    "/" + \
                                   std::to_string( static_cast<int>(m_RPGComponent->GetStat(RPGStats::MAX_HEALTH)) );

		viewStrategy->DebugRenderText(healthString, pos, 12.0f, sf::Color::Yellow);
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