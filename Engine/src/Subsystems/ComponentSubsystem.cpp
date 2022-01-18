#include "ComponentSubsystem.h"

#include "../Core/GameObject.h"

namespace Engine
{
    uint32_t ComponentSubsystem::m_nextSubsystemID = 0;

    void ComponentSubsystem::RegisterComponent(IComponent* component)
    {
        m_registeredComponents.emplace_back(component);
    }

    void ComponentSubsystem::UnregisterComponent(IComponent* component)
    {
        m_registeredComponents.erase(std::remove(m_registeredComponents.begin(), m_registeredComponents.end(), component), m_registeredComponents.end());
    }

    void ComponentSubsystem::Update(float dt) 
    {
        for (auto c : m_registeredComponents)
            if(c->Owner.ShouldUpdate())
                c->Update(dt);
    };
};