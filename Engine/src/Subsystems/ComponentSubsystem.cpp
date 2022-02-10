#include "ComponentSubsystem.h"

#include "../Core/GameObject.h"

namespace Engine
{
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