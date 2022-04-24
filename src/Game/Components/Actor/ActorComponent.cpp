#include "ActorComponent.h"
#include "WeaponComponent.h"
#include <Engine/Components/Physics.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>

namespace Game
{

    ActorComponent::ActorComponent(Engine::GameObject& obj)
        : IComponent(obj)
        , m_commandsQueue()
    {
        Requires<Engine::PhysicsBodyComponent>();
    }

    void ActorComponent::OnCreate()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    ActorComponent::~ActorComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void ActorComponent::AddCommand(std::unique_ptr<ICommand> command)
    {
        m_commandsQueue.push(std::move(command));
    }
     
    // https://www.iforce2d.net/b2dtut/constant-speed
    void ActorComponent::Move(Engine::math::Vec2 dir)
    {
        auto physBody = Owner.GetComponent<Engine::PhysicsBodyComponent>();
        auto mass = physBody->GetMass();

        auto actualVelicity = physBody->GetLinearVelocity();
        dir *= 15;
        auto desiredVelocity = dir;

        auto impulse = (desiredVelocity - actualVelicity);
        impulse *= mass;
        physBody->ApplyImpulseToCenter(impulse);
    }

    void ActorComponent::Rotate(float angle)
    {
        Owner.GetTransform().Rotation = angle;
    }

    void ActorComponent::Fire()
    {
        auto weaponComp = Owner.GetComponent<WeaponComponent>();
        if (weaponComp) 
        {
            weaponComp->Fire();
        }
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