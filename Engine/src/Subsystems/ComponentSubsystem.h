#pragma once

#include "../Components/Core.h"

#include <memory>

namespace Engine
{
    class ComponentSubsystem
    {
    public:
        ComponentSubsystem() {};
        ~ComponentSubsystem() {};

        void RegisterComponent(IComponent* component);
        void UnregisterComponent(IComponent* component);

        void Update(float dt);
    protected:
        static uint32_t m_nextSubsystemID;
    private:
        std::vector< IComponent* > m_registeredComponents;
    };
}