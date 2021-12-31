#include "ActorSubsystem.h"

#include "../Core/GameObject.h"

namespace Game
{
    ActorSubsystem::ActorSubsystem()
        : m_actors()
        , m_inputs()
    {
        LOG_INFO("Created ActorSubsystem");
    }

    ActorSubsystem::~ActorSubsystem()
    {
        LOG_INFO("Destroyed ActorSubsystem");
    }

    void ActorSubsystem::RegisterComponent(IComponent* component)
    {
        if (auto inputComponent = dynamic_cast<InputComponent*>(component))
        {
            m_inputs.emplace_back(inputComponent);
            LOG_INFO("{ActorSubsystem} registered InputComponent from ID: %d", inputComponent->Owner.ID);
        }
        else if (auto actorComponent = dynamic_cast<ActorComponent*>(component))
        {
            m_actors.emplace_back(actorComponent);
            LOG_INFO("{ActorSubsystem} registered ActorComponent from ID: %d", actorComponent->Owner.ID);
        }
    }

    void ActorSubsystem::UnregisterComponent(IComponent* component)
    {
        if (auto inputComponent = dynamic_cast<InputComponent*>(component))
        {
            m_inputs.erase(std::remove(m_inputs.begin(), m_inputs.end(), inputComponent), m_inputs.end());
            LOG_INFO("{ActorSubsystem} unregistered InputComponent from ID: %d", inputComponent->Owner.ID);
        }
        else if (auto actorComponent = dynamic_cast<ActorComponent*>(component))
        {
            m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), actorComponent), m_actors.end());
            LOG_INFO("{ActorSubsystem} unregistered ActorComponent from ID: %d", actorComponent->Owner.ID);
        }
    }

    void ActorSubsystem::Update(float dt)
    {
        // Update input components
        for (auto iC : m_inputs)
            iC->Update(dt);

        // Update actor components
        for (auto aC : m_actors)
            aC->Update(dt);
    }
};